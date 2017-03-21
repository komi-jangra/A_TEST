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
 *  ID: $Id: ss7_mgmt.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:00  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/05/06 05:53:58  adutta
 * LOG: MTP route pegs declaration
 * LOG:
 * LOG: Revision 9.2  2005/04/06 10:24:39  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.17  2005/03/21 13:53:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.12.2.6.2.2.8.3  2005/01/31 10:46:41  snagesh
 * LOG: Added OSS APIs and moved management data to intern.h files
 * LOG:
 * LOG: Revision 7.12.2.6.2.2.8.2  2004/12/31 06:07:30  sbabu
 * LOG: TCAP OAM changes
 * LOG:
 * LOG: Revision 7.12.2.6.2.2.8.1  2004/12/29 13:16:28  csireesh
 * LOG: ISUP OAM changes
 * LOG:
 * LOG: Revision 7.12.2.6.2.2  2004/08/10 11:50:59  kannanp
 * LOG: Changes for MTP3 pegs & alarms - propagated from TCS.
 * LOG:
 * LOG: Revision 7.12.2.6.2.1  2004/06/22 11:49:34  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.12.2.6  2003/12/23 12:46:07  ssingh
 * LOG: Bug #683, new functions for clearing indivisual Msg based pegs.
 * LOG:
 * LOG: Revision 7.12.2.5  2003/12/05 07:10:26  ssingh
 * LOG: Bug #683 fix. Message based pegs propagated to Release 6.3
 * LOG:
 * LOG: Revision 7.12.2.4  2003/10/22 13:17:29  sjaddu
 * LOG: isup_variant.h is removed.
 * LOG:
 * LOG: Revision 7.12.2.3  2003/05/07 09:56:15  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 7.12.2.2  2003/03/27 12:36:19  akumar
 * LOG: Modified while Adding MML in PR_6.3
 * LOG:
 * LOG: Revision 7.12.2.1  2003/03/17 11:53:19  akumar
 * LOG: Added ITU MML in PR_6.3 Branch
 * LOG:
 * LOG: Revision 7.12  2003/02/07 12:53:36  ssingh
 * LOG: MML commands added for get/set congestion level.
 * LOG:
 * LOG: Revision 7.11  2003/02/05 00:53:02  sjaddu
 * LOG: Added Xchange type to destination.
 * LOG:
 * LOG: Revision 7.10  2003/01/29 19:02:51  sjaddu
 * LOG: Peg structure and func is changed for ISUP.
 * LOG:
 * LOG: Revision 7.9  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.8  2003/01/20 20:08:15  ngoel
 * LOG: rename ssn state define to avoid conflict
 * LOG:
 * LOG: Revision 7.7  2003/01/10 22:35:55  sjaddu
 * LOG: Added OSS interface for ISUP.
 * LOG:
 * LOG: Revision 7.6  2002/12/27 05:43:36  ssingh
 * LOG: Added ISUP MML command for setting CIC state.
 * LOG:
 * LOG: Revision 7.5  2002/12/23 14:13:44  ngoel
 * LOG: add control for each trace level using mml
 * LOG:
 * LOG: Revision 7.4  2002/11/22 07:28:28  sjaddu
 * LOG: More ISUP MML functions are added.
 * LOG:
 * LOG: Revision 7.3  2002/11/19 12:53:10  sjaddu
 * LOG: Added ISUP MML helper functions.
 * LOG:
 * LOG: Revision 7.2  2002/11/08 06:20:47  sjaddu
 * LOG: Added ISUP MML functions.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.16  2002/08/25 23:41:18  ngoel
 * LOG: remove syntax error
 * LOG:
 * LOG: Revision 6.15  2002/07/26 13:34:34  ngoel
 * LOG: add SetLocalSS for TCAP
 * LOG:
 * LOG: Revision 6.14  2002/07/15 14:47:31  ngoel
 * LOG: add TCAP MML functions
 * LOG:
 * LOG: Revision 6.13  2002/07/09 17:07:56  ngoel
 * LOG: remove warnings
 * LOG:
 * LOG: Revision 6.12  2002/07/08 00:04:23  ngoel
 * LOG: add linkset to sccp ss and pc info
 * LOG:
 * LOG: Revision 6.11  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.10  2002/06/19 17:11:00  mmiers
 * LOG: Add MTP3 OAM APIs
 * LOG:
 * LOG: Revision 6.9  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.8  2002/05/13 18:21:48  mmiers
 * LOG: Switch PC order.  Normalize SCCP mgmt API
 * LOG:
 * LOG: Revision 6.7  2002/05/09 14:42:53  hxing
 * LOG: Make the class records extern
 * LOG:
 * LOG: Revision 6.6  2002/05/03 19:59:51  hxing
 * LOG: Modify SCCP Mgmt function signatures.
 * LOG:
 * LOG: Revision 6.5  2002/04/29 17:00:12  mmiers
 * LOG: Add first cut of mgmt API for TCAP, MTP3.
 * LOG:
 * LOG: Revision 6.4  2002/04/29 16:40:12  mmiers
 * LOG: Finish off pass 1 of the mgmt API
 * LOG:
 * LOG: Revision 6.3  2002/04/29 15:42:29  mmiers
 * LOG: Add SCCP management class records
 * LOG:
 * LOG: Revision 6.2  2002/04/24 15:55:37  mmiers
 * LOG: Add SCCP management interface.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.9  2001/12/15 01:19:49  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 1.8  2001/12/11 23:49:52  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 1.7  2001/11/20 20:15:52  mmiers
 * LOG: Tab removal
 * LOG:
 * LOG: Revision 1.6  2001/11/13 16:14:23  vnitin
 * LOG: few definitions
 * LOG:
 * LOG: Revision 1.5  2001/11/09 20:19:54  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 1.4  2001/10/26 16:53:27  rsonak
 * LOG: Added more triggers
 * LOG:
 * LOG: Revision 1.3  2001/10/23 22:57:12  rsonak
 * LOG: MGMT inhibit trigger added
 * LOG:
 * LOG: Revision 1.2  2001/10/03 22:16:39  mmiers
 * LOG: Debugging additions.
 * LOG:
 * LOG: Revision 1.1  2001/09/28 21:34:36  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.24  2001/09/26 22:43:14  mmiers
 * LOG: Add checking to SLM
 * LOG:
 * LOG: Revision 5.23  2001/09/26 21:28:44  mmiers
 * LOG: SRM is essentially complete, but a few more tricks are needed.
 * LOG: Other stuff is more fixme removal.
 * LOG:
 * LOG: Revision 5.22  2001/09/17 23:43:37  mmiers
 * LOG: Walkthroughs.
 * LOG:
 * LOG: Revision 5.21  2001/09/14 17:38:53  rsonak
 * LOG: Changeback code is an ITS_OCTET, so max 255
 * LOG:
 * LOG: Revision 5.20  2001/09/13 15:50:30  mmiers
 * LOG: Arg format.
 * LOG:
 * LOG: Revision 5.19  2001/09/12 22:53:59  mmiers
 * LOG: TPRC
 * LOG:
 * LOG: Revision 5.18  2001/09/12 22:02:45  rsonak
 * LOG: Solidify TLAC
 * LOG:
 * LOG: Revision 5.17  2001/09/12 21:06:03  mmiers
 * LOG: Today's installment.
 * LOG:
 * LOG: Revision 5.16  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.15  2001/09/11 20:14:15  mmiers
 * LOG: SRM is as done as far as I can get it.
 * LOG:
 * LOG: Revision 5.14  2001/09/06 15:33:32  mmiers
 * LOG: Cleanup.  Add reserved NI use to TCAP.
 * LOG:
 * LOG: Revision 5.13  2001/09/05 23:05:45  mmiers
 * LOG: Working MTP2 into the scene.
 * LOG:
 * LOG: Revision 5.12  2001/08/31 14:22:10  mmiers
 * LOG: Brainstorming fixes.
 * LOG:
 * LOG: Revision 5.11  2001/08/30 19:29:44  mmiers
 * LOG: Work on SRM
 * LOG:
 * LOG: Revision 5.10  2001/08/28 21:25:50  rsonak
 * LOG: More triggers
 * LOG:
 * LOG: Revision 5.9  2001/08/28 21:04:45  mmiers
 * LOG: Merge.
 * LOG:
 * LOG: Revision 5.8  2001/08/28 20:47:49  mmiers
 * LOG: More MTP3 work
 * LOG:
 * LOG: Revision 5.7  2001/08/27 22:57:05  mmiers
 * LOG: Updates from ANSI-96 SDL.
 * LOG:
 * LOG: Revision 5.6  2001/08/27 19:34:55  mmiers
 * LOG: Revert to old args.
 * LOG:
 * LOG: Revision 5.5  2001/08/23 23:03:37  rsonak
 * LOG: TLAC sheet 6
 * LOG:
 * LOG: Revision 5.4  2001/08/22 17:18:52  mmiers
 * LOG: Finish typing the STM functions.
 * LOG:
 * LOG: Revision 5.3  2001/08/22 17:01:01  mmiers
 * LOG: Snapshot (arg types for STM).
 * LOG:
 * LOG: Revision 5.2  2001/08/21 20:21:31  mmiers
 * LOG: Start adding in the missing code.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.23  2001/08/14 23:10:47  mmiers
 * LOG: A little cleanup.  Deep thought underway.
 * LOG:
 * LOG: Revision 4.22  2001/08/09 22:25:56  mmiers
 * LOG: TSRC is in.  TLAC is left.
 * LOG:
 * LOG: Revision 4.21  2001/08/09 01:08:04  mmiers
 * LOG: Fill in the rest of STM.  Only TLAC and TSRC left.
 * LOG:
 * LOG: Revision 4.20  2001/08/08 22:35:09  mmiers
 * LOG: Update with STM implementation.
 * LOG:
 * LOG: Revision 4.19  2001/08/08 00:55:03  mmiers
 * LOG: Add timer handling.
 * LOG:
 * LOG: Revision 4.18  2001/08/07 22:01:51  mmiers
 * LOG: Add MTP3 API, some timers.
 * LOG:
 * LOG: Revision 4.17  2001/08/06 23:05:39  rsonak
 * LOG: Added more triggers
 * LOG:
 * LOG: Revision 4.16  2001/08/06 21:28:00  rsonak
 * LOG: Added more STM, SMH triggers
 * LOG:
 * LOG: Revision 4.15  2001/08/03 21:47:03  rsonak
 * LOG: Added MTP3 timers, timer-states and STM triggers/prototypes
 * LOG:
 * LOG: Revision 4.14  2001/08/03 19:51:06  mmiers
 * LOG: Final variable rename.
 * LOG:
 * LOG: Revision 4.13  2001/08/03 19:45:49  mmiers
 * LOG: Rename a few things.
 * LOG:
 * LOG: Revision 4.12  2001/08/03 19:38:25  mmiers
 * LOG: First pass complete.  Off to read specs for a while.
 * LOG:
 * LOG: Revision 4.11  2001/08/02 23:14:32  mmiers
 * LOG: Updates.
 * LOG:
 * LOG: Revision 4.10  2001/08/02 22:02:37  mmiers
 * LOG: Add SLT and MGMT for MTP3.
 * LOG:
 * LOG: Revision 4.9  2001/08/02 21:43:36  mmiers
 * LOG: SMH and SRM are converted to the new form.
 * LOG:
 * LOG: Revision 4.8  2001/08/02 17:00:21  mmiers
 * LOG: Add sif, len to srm and slt mains.
 * LOG:
 * LOG: Revision 4.7  2001/08/02 16:55:35  mmiers
 * LOG: Restructured for new layout.
 * LOG:
 * LOG: Revision 4.6  2001/08/01 21:50:29  mmiers
 * LOG: Note triggers and subsystems.
 * LOG:
 * LOG: Revision 4.5  2001/07/27 15:06:54  mmiers
 * LOG: Start SLM.
 * LOG:
 * LOG: Revision 4.4  2001/07/26 23:20:06  mmiers
 * LOG: More MTP3.  Just about got SRM.
 * LOG:
 * LOG: Revision 4.3  2001/06/07 21:49:43  mmiers
 * LOG: Make sure it builds.
 * LOG:
 * LOG: Revision 4.2  2001/06/07 21:35:06  mmiers
 * LOG: Start MTP3.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2001/04/02 21:20:24  mmiers
 * LOG: Align the string names.
 * LOG:
 * LOG: Revision 3.2  2001/03/28 21:11:26  mmiers
 * LOG: Change the names to match config.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:42  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:42  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/07/13 15:40:48  mmiers
 * LOG:
 * LOG:
 * LOG: Make trace file names consistent.
 * LOG:
 * LOG: Revision 1.3  1999/03/17 18:39:51  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.2  1998/11/11 00:45:29  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.1  1998/09/29 01:24:57  mmiers
 * LOG: Implement needed MTP3 functionality.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

/*****************************************************************************
 *  Revision History:
 * ---------------------------------------------------------------------------
 * Name        Date        Reference        Description
 * ---------------------------------------------------------------------------
 * kramesh     04-05-2005  BCGI Problem     Local Cong level and outgoing REL
 *                         #488             - ISUP_CFG_ALLDEST_INFO new struct
 *                                          - ISUP_GetDestIterProc added.
 * ****************************************************************************/
#ifndef SS7_MGMT_H
#define SS7_MGMT_H

#ident "$Id: ss7_mgmt.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $"

#include <its.h>
#include <its_pegs.h>
#include <its_behaviors.h>
#include <its_alarm.h>
#include <its_timers.h>
#include <isup_variants.h>
#include <sccp_pegs.h>
#include <mtp3_pegs.h>

#include <dbc_serv.h>

#define ISUP_CFG_MAX_TIMERS 62
#define ISUP_CFG_MAX_TIMERS_CCITT 39
#define ISUP_CFG_MAX_TIMERS_ANSI 51

#if defined(__cplusplus)
extern "C"
{
#endif

/*****************************************************************************
 *
 * Generic management data.
 *
 *****************************************************************************/
/*
 * alarm levels
 */
typedef enum
{
    ALARM_OFF,
    ALARM_DEFAULT,
    ALARM_DEBUG,
    ALARM_DETAIL
}
MGMT_AlarmLevel;


/*******************************
 *
 *       MTP3 OSS APIs
 *
 *******************************/

#define MTP3_ALL_PEGS       255

/* Structure for MTP3 General Config */
typedef struct MTP3_GeneralCfg
{
    MGMT_AlarmLevel     alarmLevel;
    ITS_BOOLEAN         debugTrace;
    ITS_OCTET           debugTraceOutput;
    ITS_BOOLEAN         warningTrace;
    ITS_OCTET           warningTraceOutput;
    ITS_BOOLEAN         errorTrace;
    ITS_OCTET           errorTraceOutput;
    ITS_BOOLEAN         criticalTrace;
    ITS_OCTET           criticalTraceOutput;
    ITS_BOOLEAN         eventTrace;
    ITS_OCTET           eventTraceOutput;
}
MTP3_GeneralCfg;

/* Structure for Link Info */
typedef struct SS7_LinkInfo
{
    ITS_OCTET           linkSet;            /* linkset id */
    ITS_OCTET           linkCode;           /* signalling link code */
    SS7_Family          family;             /* protocol family */
    ITS_USHORT          id;                 /* transport: local data */
    ITS_BOOLEAN         initActive;         /* activate when link set activates */
    ITS_BOOLEAN         localLink;          /* link is on local node */
    ITS_OCTET           priority;           /* priority in this link set */
    ITS_BOOLEAN         isUp;               /* active link */
    ITS_BOOLEAN         isAllowed;          /* usable link */
    ITS_OCTET           active;             /* from routing perspective */
    ITS_BOOLEAN         congLevel;          /* congestion level */
    LINK_AvailableState availableState;
    ITS_BOOLEAN         testPassed;         /* SLTM/SLTA says ok */
}
SS7_LinkInfo;

/* Structure for Linkset Info */
typedef struct SS7_LinkSetInfo
{
    ITS_OCTET               linkSet;    /* link set id */
    ITS_UINT                lpc;        /* local point code for link set */
    ITS_UINT                adjacent;   /* adjacent point code */
    ITS_OCTET               ni;         /* network indicator */
    SS7_Family              family;     /* protocol family */
    ITS_UINT                numLinks;   /* number of entries in link set */
    ITS_BOOLEAN             adjSTP;     /* adjacent is an STP */
    ITS_BOOLEAN             isUp;       /* link set is active */
}
SS7_LinkSetInfo;

typedef struct SS7_LinkInfo *SS7_LinkInfoPtr ;
typedef struct SS7_LinkSetInfo *SS7_LinkSetInfoPtr ;

/* Structure for Destination Info */
typedef struct SS7_DestInfo
{
    ITS_UINT                dpc;        /* point code */
    ITS_OCTET               sio;        /* network indicator */
    SS7_Family              family;     /* protocol family */
    DEST_Status             status;     /* dest status */
}
SS7_DestInfo;


/*
 * * * * * * ANSI MTP3 OSS APIs * * * * *
 */

/*
 * MTP3 Start and Shutdown
 */
ITSSS7DLLAPI void MTP3_OSS_Start_ANSI();
ITSSS7DLLAPI void MTP3_OSS_Shutdown_ANSI ();

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetGeneralCfg_ANSI(MTP3_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT MTP3_OSS_SetGeneralCfg_ANSI(MTP3_GeneralCfg* genCfg);

/*
 * Behavior Control
 */
ITSSS7DLLAPI void MTP3_OSS_SetBehavior_ANSI(ITS_BOOLEAN isStp,
                                            ITS_BOOLEAN handleSpareNic);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetBehavior_ANSI(ITS_BOOLEAN* isStp,
                                               ITS_BOOLEAN* hadleSpareNic);

/*
 * Link/Linkset Inhibit/Uninhibit/Activate/Deactivate
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_InhibitLink_ANSI(ITS_OCTET linkSet,
                                               ITS_OCTET linkCode);
ITSSS7DLLAPI ITS_INT MTP3_OSS_UninhibitLink_ANSI(ITS_OCTET linkSet,
                                                 ITS_OCTET linkCode);

ITSSS7DLLAPI ITS_INT MTP3_OSS_DeactivateLink_ANSI(ITS_OCTET linkSet,
                                                  ITS_OCTET linkCode);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ActivateLink_ANSI(ITS_OCTET linkSet,
                                                ITS_OCTET linkCode);

ITSSS7DLLAPI ITS_INT MTP3_OSS_DeactivateLinkset_ANSI(ITS_OCTET linkSet);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ActivateLinkset_ANSI(ITS_OCTET linkSet);

/*
 * Get Linkset and Link Info
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetLinkset_ANSI(ITS_OCTET linkSet,
                                              SS7_LinkSetInfo* linkSetInfoPtr,
                                              ITS_OCTET* numLinksets);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetLink_ANSI(ITS_OCTET linkSet,
                                           ITS_OCTET linkCode,
                                           SS7_LinkInfo* linkInfoPtr);

/*
 * Remote/Local PC Add/Remove/Get
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_AddRemotePC_ANSI(ITS_UINT rpc,
                                               ITS_OCTET ni,
                                               ITS_OCTET linkSet,
                                               SS7_Family fmly);
ITSSS7DLLAPI ITS_INT MTP3_OSS_RemoveRemotePC_ANSI(ITS_UINT rpc,
                                                  ITS_OCTET ni,
                                                  ITS_OCTET linkSet,
                                                  SS7_Family fmly);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetRemotePC_ANSI(SS7_DestInfo *remPc,
                                               ITS_OCTET* numDests);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetLocalPC_ANSI(SS7_DestInfo *localPc,
                                              ITS_OCTET* numDests);

/*
 * Linkset Add/Remove
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_AddLinkset_ANSI(ITS_OCTET linkSet,
                                              SS7_Family family,
                                              ITS_UINT lpc,
                                              ITS_UINT apc,
                                              ITS_UINT ni);
ITSSS7DLLAPI ITS_INT MTP3_OSS_RemoveLinkset_ANSI(ITS_OCTET linkset);

/*
 * Link Add/Remove
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_AddLink_ANSI(ITS_OCTET linkSet,
                                           ITS_OCTET linkCode,
                                           ITS_UINT transId);
ITSSS7DLLAPI ITS_INT MTP3_OSS_RemoveLink_ANSI(ITS_OCTET linkset,
                                              ITS_OCTET linkCode);

/*
 * Get/Clear Peg Values
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetGeneralPegs_ANSI(MTP3_GenPegs*);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetLinkPegs_ANSI(ITS_OCTET linkSet,
                                               ITS_OCTET linkCode,
                                               MTP3_LinkPegs* linkPegs);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetDpcPegs_ANSI(ITS_UINT pc,
                                               ITS_UINT ni,
                                               MTP3_RoutePegs* routePegs);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ClearGeneralPeg_ANSI(ITS_UINT pegId);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ClearLinkPeg_ANSI(ITS_OCTET linkSet,
                                                 ITS_OCTET linkCode,
                                                 ITS_UINT pegId);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ClearDpcPeg_ANSI(ITS_UINT pc,
                                                 ITS_UINT ni,
                                                 ITS_UINT pegId);




/*
 * * * * * * CCITT MTP3 OSS APIs * * * * *
 */

/*
 * MTP3 Start and Shutdown
 */
ITSSS7DLLAPI void MTP3_OSS_Start_CCITT();
ITSSS7DLLAPI void MTP3_OSS_Shutdown_CCITT ();

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetGeneralCfg_CCITT(MTP3_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT MTP3_OSS_SetGeneralCfg_CCITT(MTP3_GeneralCfg* genCfg);

/*
 * Behavior Control
 */
ITSSS7DLLAPI void MTP3_OSS_SetBehavior_CCITT(ITS_BOOLEAN isStp,
                                             ITS_BOOLEAN handleSpareNic);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetBehavior_CCITT(ITS_BOOLEAN* isStp,
                                                ITS_BOOLEAN* hadleSpareNic);

/*
 * Link/Linkset Inhibit/Uninhibit/Activate/Deactivate
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_InhibitLink_CCITT(ITS_OCTET linkSet,
                                                ITS_OCTET linkCode);
ITSSS7DLLAPI ITS_INT MTP3_OSS_UninhibitLink_CCITT(ITS_OCTET linkSet,
                                                  ITS_OCTET linkCode);

ITSSS7DLLAPI ITS_INT MTP3_OSS_DeactivateLink_CCITT(ITS_OCTET linkSet,
                                                   ITS_OCTET linkCode);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ActivateLink_CCITT(ITS_OCTET linkSet,
                                                 ITS_OCTET linkCode);

ITSSS7DLLAPI ITS_INT MTP3_OSS_DeactivateLinkset_CCITT (ITS_OCTET linkSet);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ActivateLinkset_CCITT (ITS_OCTET linkSet);

/*
 * Get Linkset and Link Info
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetLinkset_CCITT(ITS_OCTET linkSet,
                                               SS7_LinkSetInfo* linkSetInfoPtr,
                                               ITS_OCTET* numLinksets);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetLink_CCITT(ITS_OCTET linkSet,
                                            ITS_OCTET linkCode,
                                            SS7_LinkInfo* linkInfoPtr);

/*
 * Remote/Local PC Add/Remove/Get
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_AddRemotePC_CCITT(ITS_UINT rpc,
                                                ITS_OCTET ni,
                                                ITS_OCTET linkSet,
                                                SS7_Family fmly);
ITSSS7DLLAPI ITS_INT MTP3_OSS_RemoveRemotePC_CCITT(ITS_UINT rpc,
                                                   ITS_OCTET ni,
                                                   ITS_OCTET linkSet,
                                                   SS7_Family fmly);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetRemotePC_CCITT(SS7_DestInfo *remPc,
                                                ITS_OCTET* numDests);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetLocalPC_CCITT(SS7_DestInfo *localPc,
                                               ITS_OCTET* numDests);

/*
 * Linkset Add/Remove
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_AddLinkset_CCITT(ITS_OCTET linkSet,
                                               SS7_Family family,
                                               ITS_UINT lpc,
                                               ITS_UINT apc,
                                               ITS_UINT ni);
ITSSS7DLLAPI ITS_INT MTP3_OSS_RemoveLinkset_CCITT(ITS_OCTET linkset);

/*
 * Link Add/Remove
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_AddLink_CCITT(ITS_OCTET linkSet,
                                            ITS_OCTET linkCode,
                                            ITS_UINT transId);
ITSSS7DLLAPI ITS_INT MTP3_OSS_RemoveLink_CCITT(ITS_OCTET linkset,
                                               ITS_OCTET linkCode);

/*
 * Get/Clear Peg Values
 */
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetGeneralPegs_CCITT(MTP3_GenPegs*);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetLinkPegs_CCITT(ITS_OCTET linkSet,
                                                ITS_OCTET linkCode,
                                                MTP3_LinkPegs* linkPegs);
ITSSS7DLLAPI ITS_INT MTP3_OSS_GetDpcPegs_CCITT(ITS_UINT pc,
                                               ITS_UINT ni,
                                               MTP3_RoutePegs* routePegs);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ClearGeneralPeg_CCITT(ITS_UINT pegId);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ClearLinkPeg_CCITT(ITS_OCTET linkSet,
                                                  ITS_OCTET linkCode,
                                                  ITS_UINT pegId);
ITSSS7DLLAPI ITS_INT MTP3_OSS_ClearDpcPeg_CCITT(ITS_UINT pc, 
                                                ITS_UINT ni, 
                                                ITS_UINT pegId);



/*******************************
 *
 *       ISUP OSS APIs
 *
 *******************************/

#define ISUP_ALL_PEGS 255

/* Structure for ISUP General Config */
typedef struct ISUP_GeneralCfg
{
    MGMT_AlarmLevel     alarmLevel;
    ITS_BOOLEAN         debugTrace;
    ITS_OCTET           debugTraceOutput;
    ITS_BOOLEAN         warningTrace;
    ITS_OCTET           warningTraceOutput;
    ITS_BOOLEAN         errorTrace;
    ITS_OCTET           errorTraceOutput;
    ITS_BOOLEAN         criticalTrace;
    ITS_OCTET           criticalTraceOutput;
    ITS_BOOLEAN         eventTrace;
    ITS_OCTET           eventTraceOutput;
} ISUP_GeneralCfg;

/* Structure for ISUP Configuration Key */
typedef struct
{
    ITS_UINT    opc;
    ITS_UINT    dpc;
    ITS_OCTET   sio;
}
ISUP_CFG_KEY;

#if defined(ANSI)
#define ISUP_MAX_CFG_CICS_PER_CKGP 24
#else
#define ISUP_MAX_CFG_CICS_PER_CKGP 32
#endif

/* Structure for Circuit Group Information */
typedef struct
{
    ITS_USHORT          ckgp_id;
    ITS_UINT            usable_cics[1];
    ITS_OCTET           contl[ISUP_MAX_CFG_CICS_PER_CKGP];
}
ISUP_CFG_CKGP_INFO;

/* Enumeration for Exchange Type */
typedef enum
{
    ISUP_CFG_EXCHANGE_TYPE_A =0,
    ISUP_CFG_EXCHANGE_TYPE_B,

    ISUP_CFG_EXCHANGE_TYPE_INV
}
ISUP_CFG_EXCHANGE_TYPE;

/* Enumeration for type of timer handling */
typedef enum
{
    ISUP_CFG_TMR_HNDL_STACK,
    ISUP_CFG_TMR_HNDL_APP
}
ISUP_CFG_TMR_HNDL;

/* Structure for Timer Info */
typedef struct
{
    ISUP_CFG_TMR_HNDL    tmr_cfg_hndl_layer;
    ITS_UINT             tmr_cfg_value;
}
ISUP_CFG_TMR_INFO;

/* Enumeration for Destination Status */
typedef enum
{
    ISUP_CFG_DEST_UNREACHABLE = 0,
    ISUP_CFG_DEST_REACHABLE
}
ISUP_CFG_DEST_STATUS;

/* Enumeration for Congestion Levels */
typedef enum
{
    ISUP_CFG_RMTCONGES_OFF,
    ISUP_CFG_RMTCONGES_LEVEL1,
    ISUP_CFG_RMTCONGES_LEVEL2,
    ISUP_CFG_RMTCONGES_LEVEL3
}
ISUP_CFG_CONGES;

/* Enumeration for Remote ISUP Status */
typedef enum
{
    ISUP_CFG_REMOTE_AVAILABLE = 0,
    ISUP_CFG_REMOTE_UNAVAILABLE,
    ISUP_CFG_REMOTE_UNEQUIPPED
}
ISUP_CFG_REMOTE_ISUP_STATUS;

/* Structure for Destination Info */
typedef struct
{
    ISUP_CFG_KEY                    cfg;
    ITS_INT                         variant;
    ISUP_CFG_EXCHANGE_TYPE          exchange_type;
    ISUP_CFG_CONGES                     congesInd;
    ISUP_CFG_DEST_STATUS            dest_reachable;
    ISUP_CFG_REMOTE_ISUP_STATUS     remote_isup_stat;
    ISUP_CFG_TMR_INFO               timer_info[ISUP_CFG_MAX_TIMERS];
}
ISUP_CFG_DEST_INFO;

/* Structure for ISUP Peg Info */
typedef struct
{
    ITS_UINT    pegId;
    ITS_INT     pegVal;
    char        pegDesc[ITS_PATH_MAX];
}
ISUP_CFG_PEGS;

/* Destination info struct */

typedef struct
{
    ISUP_CFG_DEST_INFO **info;
    int *noEnt;
}
ISUP_CFG_ALLDEST_INFO;



/*
 * * * * * * ANSI ISUP OSS APIs * * * * *
 */

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetGeneralCfg_ANSI(ISUP_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetGeneralCfg_ANSI(ISUP_GeneralCfg* genCfg);

/*
 * CICs Add/Delete/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddCics_ANSI(ISUP_CFG_KEY cfg, 
                                           ITS_USHORT cic,
                                           ITS_USHORT range, 
                                           ITS_OCTET ctrl);
ITSSS7DLLAPI ITS_INT ISUP_OSS_DeleteCics_ANSI(ISUP_CFG_KEY cfg, 
                                              ITS_USHORT cic, 
                                              ITS_USHORT range);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCics_ANSI(ISUP_CFG_KEY cfg, 
                                           ISUP_CFG_CKGP_INFO** cics,
                                           int* numCics);

/*
 * CIC State Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCicState_ANSI(ISUP_CFG_KEY cfg,
                                               ITS_USHORT cic,
                                               ITS_OCTET *cicState);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetCicState_ANSI(ISUP_CFG_KEY cfg,
                                               ITS_USHORT cic,
                                               ITS_OCTET cicState);

/*
 * Dest Info Add/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddDestInfo_ANSI(ISUP_CFG_KEY cfg,
                                               ISUP_VAR_TYPE variant,
                                               ISUP_CFG_EXCHANGE_TYPE exchType);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetDestInfo_ANSI(ISUP_CFG_KEY cfg,
                                               ISUP_CFG_DEST_INFO* info);

/*
 * Exchange Type Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetExchangeType_ANSI(ISUP_CFG_KEY cfg, 
                                                   ISUP_CFG_EXCHANGE_TYPE exchType);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetExchangeType_ANSI(ISUP_CFG_KEY cfg, 
                                                   ISUP_CFG_EXCHANGE_TYPE* exchType);

/*
 * Congestion Level Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetCongLevel_ANSI(ITS_OCTET congLevel, 
                                                ITS_UINT congValue);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCongLevel_ANSI(ITS_OCTET congLevel, 
                                                ITS_UINT* congValue);

/*
 * Variant Add
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddVariant_ANSI(ISUP_VAR_TYPE variant);

/*
 * Timers Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetTimer_ANSI(ISUP_CFG_KEY cfg,
                                            ITS_UINT timerId,
                                            ITS_UINT timerVal,
                                            ISUP_CFG_TMR_HNDL handlBy);  
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetTimers_ANSI(ISUP_CFG_KEY cfg,
                                             ISUP_CFG_TMR_INFO* timers);  

/*
 * Gen Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetGenPegs_ANSI(ISUP_CFG_PEGS* pegs, 
                                              int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearGenPeg_ANSI(ITS_OCTET pegId);

/*
 * Msg Sent Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetMsgSentPegs_ANSI(ISUP_CFG_KEY cfg,
                                                  ISUP_CFG_PEGS* pegs,
                                                  int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearMsgSentPegs_ANSI(ISUP_CFG_KEY cfg);

/*
 * Msg Received Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetMsgRcvdPegs_ANSI(ISUP_CFG_KEY cfg,
                                                  ISUP_CFG_PEGS* pegs,
                                                  int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearMsgRcvdPegs_ANSI(ISUP_CFG_KEY cfg);

/*
 * CIC Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCicPegs_ANSI(ISUP_CFG_KEY cfg,
                                              ITS_USHORT cic,
                                              ISUP_CFG_PEGS* pegs,
                                              ITS_OCTET* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearCicPeg_ANSI(ISUP_CFG_KEY cfg,
                                               ITS_USHORT cic,
                                               ITS_OCTET pegId);

/*
 * Msg Send
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendUBL_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendBLO_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendRSC_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendRLC_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendGRS_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic,
                                           ITS_USHORT range);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCGU_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic, 
                                           ITS_OCTET msgType,
                                           ITS_USHORT range,
                                           ITS_UINT status);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCGB_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic,
                                           ITS_OCTET msgType,
                                           ITS_USHORT range,
                                           ITS_UINT status);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCQM_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic,
                                           ITS_USHORT range);


/*
 * * * * * * CCITT ISUP OSS APIs * * * * *
 */

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetGeneralCfg_CCITT(ISUP_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetGeneralCfg_CCITT(ISUP_GeneralCfg* genCfg);

/*
 * CICs Add/Delete/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddCics_CCITT(ISUP_CFG_KEY cfg, 
                                            ITS_USHORT cic,
                                            ITS_USHORT range, 
                                            ITS_OCTET ctrl);
ITSSS7DLLAPI ITS_INT ISUP_OSS_DeleteCics_CCITT(ISUP_CFG_KEY cfg, 
                                               ITS_USHORT cic, 
                                               ITS_USHORT range);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCics_CCITT(ISUP_CFG_KEY cfg, 
                                            ISUP_CFG_CKGP_INFO** cics,
                                            int* numCics);

/*
 * CIC State Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCicState_CCITT(ISUP_CFG_KEY cfg,
                                                ITS_USHORT cic,
                                                ITS_OCTET *cicState);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetCicState_CCITT(ISUP_CFG_KEY cfg,
                                                ITS_USHORT cic,
                                                ITS_OCTET cicState);

/*
 * Dest Info Add/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddDestInfo_CCITT(ISUP_CFG_KEY cfg,
                                                ISUP_VAR_TYPE variant,
                                                ISUP_CFG_EXCHANGE_TYPE exchType);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetDestInfo_CCITT(ISUP_CFG_KEY cfg,
                                                ISUP_CFG_DEST_INFO* info);

/* Get configuration and status information of all the destinations */
ITSSS7DLLAPI int ISUP_GetDestIterProc_ANSI(ITS_INT context, ITS_POINTER data,
                                           void *in, void *out);

ITSSS7DLLAPI int ISUP_GetDestIterProc_CCITT(ITS_INT context, ITS_POINTER data,
                                           void *in, void *out);
/*
 * Exchange Type Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetExchangeType_CCITT(ISUP_CFG_KEY cfg, 
                                                    ISUP_CFG_EXCHANGE_TYPE exchType);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetExchangeType_CCITT(ISUP_CFG_KEY cfg, 
                                                    ISUP_CFG_EXCHANGE_TYPE* exchType);

/*
 * Congestion Level Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetCongLevel_CCITT(ITS_OCTET congLevel, 
                                                 ITS_UINT congValue);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCongLevel_CCITT(ITS_OCTET congLevel, 
                                                 ITS_UINT* congValue);

/*
 * Variant Add
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddVariant_CCITT(ISUP_VAR_TYPE variant);

/*
 * Timers Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetTimer_CCITT(ISUP_CFG_KEY cfg,
                                              ITS_UINT timerId,
                                              ITS_UINT timerVal,
                                              ISUP_CFG_TMR_HNDL handlBy);  
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetTimers_CCITT(ISUP_CFG_KEY cfg,
                                              ISUP_CFG_TMR_INFO* timers);  

/*
 * Gen Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetGenPegs_CCITT(ISUP_CFG_PEGS* pegs, 
                                               int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearGenPeg_CCITT(ITS_OCTET pegId);

/*
 * Msg Sent Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetMsgSentPegs_CCITT(ISUP_CFG_KEY cfg,
                                                   ISUP_CFG_PEGS* pegs,
                                                   int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearMsgSentPegs_CCITT(ISUP_CFG_KEY cfg);

/*
 * Msg Received Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg,
                                                   ISUP_CFG_PEGS* pegs,
                                                   int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg);

/*
 * CIC Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCicPegs_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ISUP_CFG_PEGS* pegs,
                                            ITS_OCTET* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearCicPeg_CCITT(ISUP_CFG_KEY cfg,
                                                ITS_USHORT cic,
                                                ITS_OCTET pegId);

/*
 * Msg Send
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendUBL_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendBLO_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendRSC_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendRLC_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendGRS_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ITS_USHORT range);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCGU_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic, 
                                            ITS_OCTET msgType,
                                            ITS_USHORT range,
                                            ITS_UINT status);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCGB_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ITS_OCTET msgType,
                                            ITS_USHORT range,
                                            ITS_UINT status);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCQM_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ITS_USHORT range);


/*******************************
 *
 *       SCCP OSS APIs
 *
 *******************************/

#define SCCP_ALL_PEGS           255
#define SCCP_ALL_TIMERS         255
#define SCCP_ALL_BEHAVIORS      255

/* Structure for SCCP General Config */
typedef struct SCCP_GeneralCfg
{
    MGMT_AlarmLevel     alarmLevel;
    ITS_BOOLEAN         debugTrace;
    ITS_OCTET           debugTraceOutput;
    ITS_BOOLEAN         warningTrace;
    ITS_OCTET           warningTraceOutput;
    ITS_BOOLEAN         errorTrace;
    ITS_OCTET           errorTraceOutput;
    ITS_BOOLEAN         criticalTrace;
    ITS_OCTET           criticalTraceOutput;
    ITS_BOOLEAN         eventTrace;
    ITS_OCTET           eventTraceOutput;
} SCCP_GeneralCfg;

/* SCCP Subsystem Backup Status */
typedef enum
{
    SSN_STANDALONE,
    SSN_PRIMARY,
    SSN_SECONDARY,
    SSN_MATED
}
SCCPSubsystemBackupStatus;

/* Structure for SCCP Subsystem */
typedef struct
{
    ITS_UINT                  pointcode;
    ITS_OCTET                 ni;
    ITS_OCTET                 ssn;
    ITS_BOOLEAN               inService;
    ITS_BOOLEAN               testOn;
    ITS_INT                   variant;
    ITS_BOOLEAN               hasConcernPC;
    ITS_BOOLEAN               isLocal;
    ITS_UINT                  maxHops;
    SCCPSubsystemBackupStatus backupStatus;
    ITS_UINT                  backupPC;
    ITS_OCTET                 backupNI;
    ITS_OCTET                 backupSSN;
    ITS_BOOLEAN               backupSSNState; /* in-service or out-of-service */
    ITS_OCTET                 linkSet;
}
SCCPSubSystemInfo;

/* Structure for SCCP Concerned Subsystem */
typedef struct
{
    ITS_UINT           pc;
    ITS_OCTET          ni;
    ITS_OCTET          ssn;
    ITS_UINT           cpc;
    ITS_OCTET          cssn;
    ITS_BOOLEAN        inservice;
}
SCCPConcernedSSInfo;


/* Structure for SCCP Behaviors */
typedef struct SCCP_Behaviors
{
    ITS_BOOLEAN     useSCMG;
    ITS_BOOLEAN     propogateSCMG;
    ITS_BOOLEAN     propogateIT;
    ITS_BOOLEAN     propogateERR;
} SCCP_Behaviors;

/* Structure for SCCP Timers */
typedef struct SCCP_Timers
{
    ITS_UINT   statInfo;
    ITS_UINT   coordChg;
    ITS_UINT   ignoreSST;
    ITS_UINT   rtgStatInfo;
    ITS_UINT   conn;
    ITS_UINT   release;
    ITS_UINT   reset;
    ITS_UINT   ias;
    ITS_UINT   iar;
    ITS_UINT   guard;
    ITS_UINT   reassembly;
    ITS_UINT   interval;
    ITS_UINT   repeatRelease;
} SCCP_Timers;


/*
 * * * * * * ANSI SCCP OSS APIs * * * * *
 */

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetGeneralCfg_ANSI(SCCP_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SetGeneralCfg_ANSI(SCCP_GeneralCfg* genCfg);

/*
 * Behavior Control
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetBehaviors_ANSI(SCCP_Behaviors* behaviors);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SetBehavior_ANSI(ITS_UINT behId,
                                               ITS_BOOLEAN behValue,
                                               SCCP_Behaviors* behaviors);

/*
 * Local/Remote SSN Add/Remove/Get
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_AddLocalSSN_ANSI(ITS_UINT pc,
                                               ITS_OCTET ni,
                                               ITS_OCTET ssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_RemoveLocalSSN_ANSI(ITS_UINT pc,
                                                  ITS_OCTET ni,
                                                  ITS_OCTET ssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_AddRemoteSSN_ANSI(ITS_UINT pc,
                                                ITS_OCTET ni,
                                                ITS_OCTET ssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_RemoveRemoteSSN_ANSI(ITS_UINT pc,
                                                   ITS_OCTET ni,
                                                   ITS_OCTET ssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetAllSSN_ANSI(SCCPSubSystemInfo** entries,
                                             ITS_UINT* numEntries);

/*
 * Concerned SSN Add/Remove/Get
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_AddConcernedSSN_ANSI(ITS_UINT pc,
                                                   ITS_OCTET ni,
                                                   ITS_OCTET ssn,
                                                   ITS_UINT cpc,
                                                   ITS_OCTET cssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_RemoveConcernedSSN_ANSI(ITS_UINT pc,
                                                      ITS_OCTET ni,
                                                      ITS_OCTET ssn,
                                                      ITS_UINT cpc,
                                                      ITS_OCTET cssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetConcernedSSN_ANSI(SCCPConcernedSSInfo** entries,
                                                   ITS_UINT* numEntries);

/*
 * Get/Clear Peg Values
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetPegs_ANSI(SCCP_Pegs* pegs);
ITSSS7DLLAPI ITS_INT SCCP_OSS_ClearPeg_ANSI(ITS_UINT pegId);

/*
 * Get/Set Timer Values
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetTimers_ANSI(SCCP_Timers* timers);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SetTimer_ANSI(ITS_UINT timerId,
                                            ITS_UINT timerValue,
                                            SCCP_Timers* timers);

/*
 * Send SSA/SSP/SST
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_SendSSA_ANSI(ITS_UINT pc,
                                           ITS_OCTET ni,
                                           ITS_OCTET ssn,
                                           ITS_UINT cpc,
                                           ITS_OCTET cssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SendSSP_ANSI(ITS_UINT pc,
                                           ITS_OCTET ni,
                                           ITS_OCTET ssn,
                                           ITS_UINT cpc,
                                           ITS_OCTET cssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SendSST_ANSI(ITS_UINT pc,
                                           ITS_OCTET ni,
                                           ITS_OCTET ssn,
                                           ITS_UINT cpc,
                                           ITS_OCTET cssn);


/*
 * * * * * * CCITT SCCP OSS APIs * * * * *
 */

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetGeneralCfg_CCITT(SCCP_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SetGeneralCfg_CCITT(SCCP_GeneralCfg* genCfg);

/*
 * Behavior Control
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetBehaviors_CCITT(SCCP_Behaviors* behaviors);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SetBehavior_CCITT(ITS_UINT behId,
                                                ITS_BOOLEAN behValue,
                                                SCCP_Behaviors* behaviors);

/*
 * Local/Remote SSN Add/Remove/Get
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_AddLocalSSN_CCITT(ITS_UINT pc,
                                                ITS_OCTET ni,
                                                ITS_OCTET ssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_RemoveLocalSSN_CCITT(ITS_UINT pc,
                                                   ITS_OCTET ni,
                                                   ITS_OCTET ssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_AddRemoteSSN_CCITT(ITS_UINT pc,
                                                 ITS_OCTET ni,
                                                 ITS_OCTET ssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_RemoveRemoteSSN_CCITT(ITS_UINT pc,
                                                    ITS_OCTET ni,
                                                    ITS_OCTET ssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetAllSSN_CCITT(SCCPSubSystemInfo** entries,
                                              ITS_UINT* numEntries);

/*
 * Concerned SSN Add/Remove/Get
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_AddConcernedSSN_CCITT(ITS_UINT pc,
                                                    ITS_OCTET ni,
                                                    ITS_OCTET ssn,
                                                    ITS_UINT cpc,
                                                    ITS_OCTET cssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_RemoveConcernedSSN_CCITT(ITS_UINT pc,
                                                       ITS_OCTET ni,
                                                       ITS_OCTET ssn,
                                                       ITS_UINT cpc,
                                                       ITS_OCTET cssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetConcernedSSN_CCITT(SCCPConcernedSSInfo** entries,
                                                    ITS_UINT* numEntries);


/*
 * Get/Clear Peg Values
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetPegs_CCITT(SCCP_Pegs* pegs);
ITSSS7DLLAPI ITS_INT SCCP_OSS_ClearPeg_CCITT(ITS_UINT pegId);

/*
 * Get/Set Timer Values
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_GetTimers_CCITT(SCCP_Timers* timers);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SetTimer_CCITT(ITS_UINT timerId,
                                             ITS_UINT timerValue,
                                             SCCP_Timers* timers);

/*
 * Send SSA/SSP/SST
 */
ITSSS7DLLAPI ITS_INT SCCP_OSS_SendSSA_CCITT(ITS_UINT pc,
                                            ITS_OCTET ni,
                                            ITS_OCTET ssn,
                                            ITS_UINT cpc,
                                            ITS_OCTET cssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SendSSP_CCITT(ITS_UINT pc,
                                            ITS_OCTET ni,
                                            ITS_OCTET ssn,
                                            ITS_UINT cpc,
                                            ITS_OCTET cssn);
ITSSS7DLLAPI ITS_INT SCCP_OSS_SendSST_CCITT(ITS_UINT pc,
                                            ITS_OCTET ni,
                                            ITS_OCTET ssn,
                                            ITS_UINT cpc,
                                            ITS_OCTET cssn);


/*******************************
 *
 *       TCAP OSS APIs
 *
 *******************************/

#define TCAP_ALL_PEGS       255
#define TCAP_ALL_TIMERS     255
#define TCAP_ALL_BEHAVIORS  255

/* Structure for TCAP General Config */
typedef struct TCAP_GeneralCfg
{
    MGMT_AlarmLevel     alarmLevel;
    ITS_BOOLEAN         debugTrace;
    ITS_OCTET           debugTraceOutput;
    ITS_BOOLEAN         warningTrace;
    ITS_OCTET           warningTraceOutput;
    ITS_BOOLEAN         errorTrace;
    ITS_OCTET           errorTraceOutput;
    ITS_BOOLEAN         criticalTrace;
    ITS_OCTET           criticalTraceOutput;
    ITS_BOOLEAN         eventTrace;
    ITS_OCTET           eventTraceOutput;
} TCAP_GeneralCfg;

/* Structure for TCAP Behaviors */
typedef struct TCAP_Behaviors
{
    ITS_BOOLEAN     useReservedNI;
} TCAP_Behaviors;

/* Structure for TCAP Timers */
typedef struct TCAP_Timers
{
    ITS_UINT    reject;
} TCAP_Timers;


/* Structure for TCAP General Pegs */
typedef struct TCAP_GenPegs
{
    ITS_UINT    appMsgSent;
    ITS_UINT    appMsgDiscarded;
    ITS_UINT    appCmpSent;
    ITS_UINT    appCmpDiscarded;
    ITS_UINT    appDlgSent;
    ITS_UINT    remDlgRcvd;
    ITS_UINT    remCmpRcvd;
    ITS_UINT    remCmpDiscarded;
    ITS_UINT    remMsgRcvd;
    ITS_UINT    remUnknownMsgRcvd;
    ITS_UINT    remMsgDiscarded;
    ITS_UINT    activeDlg;
    ITS_UINT    activeTransaction;
    ITS_UINT    appPreArrangedEndSent;
    ITS_UINT    invalidSccpRcvd;
    ITS_UINT    remSccpClass0Rcvd;
    ITS_UINT    remSccpClass1Rcvd;
    ITS_UINT    remUniRcvd;
    ITS_UINT    appSccpClass0Sent;
    ITS_UINT    appSccpClass1Sent;
    ITS_UINT    appUniSent;
    ITS_UINT    appAbortSent;
    ITS_UINT    remAbortRcvd;
    ITS_UINT    appRejectSent;
    ITS_UINT    remRejectRcvd;
    ITS_UINT    localCancel;
    ITS_UINT    remDlgSendFailed;
    ITS_UINT    appDlgSendFailed;
    ITS_UINT    appInvokeSent;
    ITS_UINT    appResultSent;
    ITS_UINT    appErrorSent;
    ITS_UINT    remInvokeRcvd;
    ITS_UINT    remResultRcvd;
    ITS_UINT    remErrorRcvd;
}TCAP_GenPegs;

/* Structure for TCAP ITU Pegs */
typedef struct TCAP_Pegs_CCITT
{
    TCAP_GenPegs genPegs;

    ITS_UINT    appOpClass1Sent;
    ITS_UINT    appOpClass2Sent;
    ITS_UINT    appOpClass3Sent;
    ITS_UINT    appOpClass4Sent;
    ITS_UINT    appBeginSent;
    ITS_UINT    appContSent;
    ITS_UINT    appEndSent;
    ITS_UINT    remBeginRcvd;
    ITS_UINT    remContRcvd;
    ITS_UINT    remEndRcvd;
} TCAP_Pegs_CCITT;

/* Structure for TCAP ANSI Pegs */
typedef struct TCAP_Pegs_ANSI
{
    TCAP_GenPegs genPegs;

    ITS_UINT    appQwopSent;
    ITS_UINT    remQwopRcvd;
    ITS_UINT    appQwipSent;
    ITS_UINT    remQwipRcvd;
    ITS_UINT    appRespSent;
    ITS_UINT    remRespRcvd;
    ITS_UINT    appCwopSent;
    ITS_UINT    remCwopRcvd;
    ITS_UINT    appCwipSent;
    ITS_UINT    remCwipRcvd;
} TCAP_Pegs_ANSI;


/*
 * * * * * * ANSI TCAP OSS APIs * * * * *
 */

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT TCAP_OSS_GetGeneralCfg_ANSI(TCAP_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT TCAP_OSS_SetGeneralCfg_ANSI(TCAP_GeneralCfg* genCfg);

/*
 * Behavior Control
 */
ITSSS7DLLAPI ITS_INT TCAP_OSS_GetBehaviors_ANSI(TCAP_Behaviors* behaviors);
ITSSS7DLLAPI ITS_INT TCAP_OSS_SetBehavior_ANSI(ITS_UINT behId,
                                               ITS_BOOLEAN behValue,
                                               TCAP_Behaviors* behaviors);

/*
 * Get/Clear Peg Values
 */
ITSSS7DLLAPI ITS_INT TCAP_OSS_GetPegs_ANSI(TCAP_Pegs_ANSI* pegs);
ITSSS7DLLAPI ITS_INT TCAP_OSS_ClearPeg_ANSI(ITS_UINT pegId);


/*
 * * * * * * CCITT TCAP OSS APIs * * * * *
 */

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT TCAP_OSS_GetGeneralCfg_CCITT(TCAP_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT TCAP_OSS_SetGeneralCfg_CCITT(TCAP_GeneralCfg* genCfg);

/*
 * Behavior Control
 */
ITSSS7DLLAPI ITS_INT TCAP_OSS_GetBehaviors_CCITT(TCAP_Behaviors* behaviors);
ITSSS7DLLAPI ITS_INT TCAP_OSS_SetBehavior_CCITT(ITS_UINT behId,
                                                ITS_BOOLEAN behValue,
                                                TCAP_Behaviors* behaviors);

/*
 * Get/Clear Peg Values
 */
ITSSS7DLLAPI ITS_INT TCAP_OSS_GetPegs_CCITT(TCAP_Pegs_CCITT* pegs);
ITSSS7DLLAPI ITS_INT TCAP_OSS_ClearPeg_CCITT(ITS_UINT pegId);

/*
 * Get/Set Timer Values
 */
ITSSS7DLLAPI ITS_INT TCAP_OSS_GetTimers_CCITT(TCAP_Timers* timers);
ITSSS7DLLAPI ITS_INT TCAP_OSS_SetTimer_CCITT(ITS_UINT timerId,
                                             ITS_UINT timerValue,
                                             TCAP_Timers* timers);


/*******************************
 *
 *       MTP2 OSS APIs
 *
 *******************************/

#define MTP2_ALL_PEGS           255

/* Structure for MTP2 General Config */
typedef struct MTP2_GeneralCfg
{
    MGMT_AlarmLevel     alarmLevel;
    ITS_BOOLEAN         debugTrace;
    ITS_OCTET           debugTraceOutput;
    ITS_BOOLEAN         warningTrace;
    ITS_OCTET           warningTraceOutput;
    ITS_BOOLEAN         errorTrace;
    ITS_OCTET           errorTraceOutput;
    ITS_BOOLEAN         criticalTrace;
    ITS_OCTET           criticalTraceOutput;
    ITS_BOOLEAN         eventTrace;
    ITS_OCTET           eventTraceOutput;
}
MTP2_GeneralCfg;

/* Structure for MTP2 General Pegs */
typedef struct MTP2_GeneralPegs
{
    ITS_UINT getDataFailed;
    ITS_UINT sendDataFailed;
    ITS_UINT localProcDown;
    ITS_UINT localProcUp;
    ITS_UINT remoteProcDown;
    ITS_UINT remoteProcUp;
    ITS_UINT statInd;
    ITS_UINT suermExpiry;
    ITS_UINT incorrectFibBsn;
    ITS_UINT congDetected;
    ITS_UINT congRecovered;
    ITS_UINT msuTx;
    ITS_UINT msuRx;
    ITS_UINT t2Expired;
    ITS_UINT t6Expired;
    ITS_UINT t7Expired;
    ITS_UINT t1Expired;             /* ADAX specific peg */
    ITS_UINT t3Expired;             /* ADAX specific peg */
    ITS_UINT remoteCongDetected;    /* ADAX specific peg */
    ITS_UINT remoteCongRecovered;   /* ADAX specific peg */
} MTP2_GeneralPegs;

/* Structure for MTP2 Link Pegs */
typedef struct MTP2_LinkPegs
{
    ITS_UINT linkFailure;
    ITS_UINT suermExpiry;
    ITS_UINT incorrectFibBsn;
    ITS_UINT t6Expired;
    ITS_UINT t7Expired;
    ITS_UINT provingFailed;
    ITS_UINT errSU;
    ITS_UINT negAck;
    ITS_UINT msuTx;
    ITS_UINT msuRx;
    ITS_UINT sifSioOctetTx;
    ITS_UINT sifSioOctetRx;
    ITS_UINT octetRtx;
    ITS_UINT msuRtx;        /* ADAX specific peg */
    ITS_UINT t2t3Expired;   /* ADAX specific peg */
    ITS_UINT sibTx;         /* ADAX specific peg */
    ITS_UINT sibRx;         /* ADAX specific peg */
} MTP2_LinkPegs;


/*
 * * * * * * MTP2 OSS APIs * * * * *
 */

/*
 * General Config
 */
ITS_INT MTP2_OSS_GetGeneralCfg(MTP2_GeneralCfg* genCfg);
ITS_INT MTP2_OSS_SetGeneralCfg(MTP2_GeneralCfg* genCfg);

/*
 * Get/Clear General Peg Values
 */
ITS_INT MTP2_OSS_GetGeneralPegs(MTP2_GeneralPegs* genPegs);
ITS_INT MTP2_OSS_ClearGeneralPeg(ITS_UINT pegId);

/*
 * Get/Clear All Link Peg Values
 */
ITS_INT MTP2_OSS_GetLinkPegs(ITS_OCTET linkSet,
                             ITS_OCTET linkCode,
                             MTP2_LinkPegs* linkPegs);
ITS_INT MTP2_OSS_ClearLinkPegs(ITS_OCTET linkSet, ITS_OCTET linkCode);


#if defined(__cplusplus)
}
#endif

#endif /* SS7_MGMT_H */

