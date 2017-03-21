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
 * LOG: Revision 8.5  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5  2003/01/30 15:06:10  mmiers
 * LOG: Misnamed timer class record.
 * LOG:
 * LOG: Revision 7.4  2003/01/16 17:12:52  mmiers
 * LOG: Move the base timer implementation to CORE
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.8  2002/08/22 19:34:26  mmiers
 * LOG: HMI needs to come after DSM, as it uses timers.
 * LOG:
 * LOG: Revision 6.7  2002/06/14 18:59:43  hdivoux
 * LOG: Correction in static linked list of features.
 * LOG:
 * LOG: Revision 6.6  2002/06/04 19:53:12  mmiers
 * LOG: Build correctly on NT in release mode
 * LOG:
 * LOG: Revision 6.5  2002/05/08 20:24:26  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 6.4  2002/05/06 15:28:03  mmiers
 * LOG: Correct build procedure
 * LOG:
 * LOG: Revision 6.3  2002/04/22 19:54:12  hdivoux
 * LOG: Move dsm feature before link feature.
 * LOG:
 * LOG: Revision 6.2  2002/04/16 21:20:30  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 00:17:20  mmiers
 * LOG: Get the thread initialization right.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 21:08:56  mmiers
 * LOG: Add LINKSET class record.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/08/13 22:23:04  mmiers
 * LOG: Split routing into two subsystems.
 * LOG:
 * LOG: Revision 4.3  2001/07/09 19:59:15  mmiers
 * LOG: Finish off shared timers.
 * LOG:
 * LOG: Revision 4.2  2001/05/04 18:30:28  mmiers
 * LOG: Move these back.  Support can't be dynamically loaded due to
 * LOG: WIN32.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.15  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.14  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.13  2001/03/02 22:44:15  mmiers
 * LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
 * LOG: always.  The rest will be loaded on demand.
 * LOG:
 * LOG: Revision 3.12  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.11  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.10  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.9  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.8  2001/01/10 19:44:00  mmiers
 * LOG: Debug new implementation.
 * LOG:
 * LOG: Revision 3.7  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.6  2000/12/19 18:53:24  mmiers
 * LOG: Correct in other place
 * LOG:
 * LOG: Revision 3.5  2000/12/19 18:52:30  mmiers
 * LOG: Typo in class feature name
 * LOG:
 * LOG: Revision 3.4  2000/11/28 23:44:29  mmiers
 * LOG: Today's SCTPTRAN installment.  About finished, just need to create
 * LOG: remote transports when clients connect/destroy when they leave.
 * LOG:
 * LOG: Revision 3.3  2000/08/22 18:53:28  mmiers
 * LOG: Track down the KDD problem.  The MEMPOOL is really finding some tricky
 * LOG: bugs.
 * LOG:
 * LOG: Revision 3.2  2000/08/18 20:41:51  mmiers
 * LOG: Set up mempool feature, dump leaks.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:02  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.9  2000/03/18 21:03:49  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 1.8  2000/02/14 17:52:50  mmiers
 * LOG:
 * LOG: Integrate TRACE and RESFILE into CORE.  Change RESFILE so that it
 * LOG: sets levels on/off from control strings in the globals segment of the
 * LOG: trace file.  Always include the TRACE and RESFILE classes.
 * LOG:
 * LOG: Revision 1.7  2000/02/02 02:20:50  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 1.6  2000/02/01 23:41:51  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more feature initialization.
 * LOG:
 * LOG: Revision 1.5  2000/02/01 23:09:13  mmiers
 * LOG:
 * LOG:
 * LOG: Auto start the license system.  Can do away with standalone *now*.
 * LOG:
 * LOG: Revision 1.4  2000/01/26 18:12:11  mmiers
 * LOG:
 * LOG:
 * LOG: Add feature processing.
 * LOG:
 * LOG: Revision 1.3  2000/01/26 18:01:23  mmiers
 * LOG:
 * LOG:
 * LOG: Start the feature processing function.
 * LOG:
 * LOG: Revision 1.4  2000/01/26 17:36:31  mmiers
 * LOG:
 * LOG:
 * LOG: Fix feature processing.
 * LOG:
 * LOG: Revision 1.3  2000/01/26 03:04:09  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 1.2  1999/12/18 00:35:38  mmiers
 * LOG: Continued tweaks.
 * LOG:
 * LOG: Revision 1.1  1999/12/17 21:50:48  mmiers
 * LOG:
 * LOG:
 * LOG: Rearrange, trying to get this right.
 * LOG:
 * LOG: Revision 2.1  1999/12/17 16:44:18  mmiers
 * LOG:
 * LOG:
 * LOG: New files.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_object.h>
#include <its_app.h>
#include <its_license.h>
#include <its_trace.h>
#include <its_iniparse.h>
#include <its_alarm.h>
#include <its_dsm.h>
#include <its_timers.h>
#if !defined(STANDALONE)
#include <its_dlsym.h>
#include <its_mem_pool.h>
#include <its_thread.h>
#include <its_transports.h>
#include <its_sockets.h>
#include <its_link.h>
#include <its_route.h>
#include <its_sctp.h>
#include <its_transport_factory.h>
#include <its_worker_factory.h>
#include <its_hmi.h>
#include <its_ftm.h>
#endif

#ident "$Id: its_classes.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/* these four are always included */
static ITS_FeatureRec   applicationFeature;
static ITS_FeatureRec   licenseFeature;
static ITS_FeatureRec   traceFeature;
static ITS_FeatureRec   alarmsFeature;
static ITS_FeatureRec   resfileFeature;
static ITS_FeatureRec   dsmFeature;
static ITS_FeatureRec   timersFeature;

/* the rest are included when SUPPORT is included */
#if !defined(STANDALONE)
static ITS_FeatureRec   dlsymFeature;
static ITS_FeatureRec   alarmFeature;
static ITS_FeatureRec   workerFactoryFeature;
static ITS_FeatureRec   transportFactoryFeature;
static ITS_FeatureRec   sctptranFeature;
static ITS_FeatureRec   mempoolFeature;
static ITS_FeatureRec   threadFeature;
static ITS_FeatureRec   transportFeature;
static ITS_FeatureRec   socketsFeature;
static ITS_FeatureRec   ss7RouteFeature;
static ITS_FeatureRec   appRouteFeature;
static ITS_FeatureRec   linkFeature;
static ITS_FeatureRec   stimersFeature;
static ITS_FeatureRec   ftmFeature;
static ITS_FeatureRec   hmiFeature;
#endif

static ITS_FeatureRec applicationFeature =
{
    &licenseFeature,                                    /* next */
    NULL,                                               /* prev */
    (ITS_Class)&itsAPPLICATION_ClassRec                 /* class */
};
static ITS_FeatureRec licenseFeature =
{
    &traceFeature,                                      /* next */
    &applicationFeature,                                /* prev */
    (ITS_Class)&itsLICENSE_ClassRec                     /* class */
};
static ITS_FeatureRec traceFeature =
{
    &alarmsFeature,                                     /* next */
    &licenseFeature,                                    /* prev */
    (ITS_Class)&itsTRACE_ClassRec                       /* class */
};
static ITS_FeatureRec alarmsFeature =
{
    &resfileFeature,                                    /* next */
    &traceFeature,                                      /* prev */
    (ITS_Class)&itsALARMS_ClassRec                      /* class */
};
static ITS_FeatureRec resfileFeature =
{
    &dsmFeature,                                        /* next */
    &alarmsFeature,                                     /* prev */
    (ITS_Class)&itsRESFILE_ClassRec                     /* class */
};
static ITS_FeatureRec dsmFeature =
{
    &timersFeature,                                     /* next */
    &resfileFeature,                                    /* prev */
    (ITS_Class)&itsDSM_InitClassRec                     /* class */
};
static ITS_FeatureRec timersFeature =
{
#if defined(STANDALONE)
    NULL,                                               /* next */
#else
    &dlsymFeature,                                      /* next */
#endif
    &dsmFeature,                                        /* prev */
    (ITS_Class)&itsTIMERS_ClassRec                      /* class */
};
#if !defined(STANDALONE)
static ITS_FeatureRec dlsymFeature =
{
    &threadFeature,                                     /* next */
    &timersFeature,                                     /* prev */
    (ITS_Class)&itsDLSYM_ClassRec                       /* class */
};
static ITS_FeatureRec threadFeature =
{
    &mempoolFeature,                                    /* next */
    &dlsymFeature,                                      /* prev */
    (ITS_Class)&itsTHREAD_ClassRec                      /* class */
};
static ITS_FeatureRec mempoolFeature =
{
    &transportFeature,                                  /* next */
    &threadFeature,                                     /* prev */
    (ITS_Class)&itsMEMPOOL_ClassRec                     /* class */
};
static ITS_FeatureRec transportFeature =
{
    &socketsFeature,                                    /* next */
    &mempoolFeature,                                    /* prev */
    (ITS_Class)&itsTRANSPORT_BaseClassRec               /* class */
};
static ITS_FeatureRec socketsFeature =
{
    &ftmFeature,                                        /* next */
    &transportFeature,                                  /* prev */
    (ITS_Class)&itsSOCKET_ClassRec                      /* class */
};
static ITS_FeatureRec ftmFeature =
{
    &linkFeature,                                       /* next */
    &ftmFeature,                                        /* prev */
    (ITS_Class)&itsFTM_InitClassRec                     /* class */
};
static ITS_FeatureRec linkFeature =
{
    &ss7RouteFeature,                                   /* next */
    &ftmFeature,                                        /* prev */
    (ITS_Class)&itsLINKSET_ClassRec                     /* class */
};
static ITS_FeatureRec ss7RouteFeature =
{
    &appRouteFeature,                                   /* next */
    &linkFeature,                                       /* prev */
    (ITS_Class)&itsSS7_ROUTE_ClassRec                   /* class */
};
static ITS_FeatureRec appRouteFeature =
{
    &stimersFeature,                                    /* next */
    &ss7RouteFeature,                                   /* prev */
    (ITS_Class)&itsAPP_ROUTE_ClassRec                   /* class */
};
static ITS_FeatureRec stimersFeature =
{
    &sctptranFeature,                                   /* next */
    &appRouteFeature,                                   /* prev */
    (ITS_Class)&itsSTIMERS_ClassRec                     /* class */
};
static ITS_FeatureRec sctptranFeature =
{
    &transportFactoryFeature,                           /* next */
    &stimersFeature,                                    /* prev */
    (ITS_Class)&itsSCTPTRAN_ClassRec                    /* class */
};
static ITS_FeatureRec transportFactoryFeature =
{
    &workerFactoryFeature,                              /* next */
    &sctptranFeature,                                   /* prev */
    (ITS_Class)&itsTRANSPORT_FACTORY_ClassRec           /* class */
};
static ITS_FeatureRec workerFactoryFeature =
{
    &alarmFeature,                                      /* next */
    &transportFactoryFeature,                           /* prev */
    (ITS_Class)&itsWORKER_FACTORY_ClassRec              /* class */
};
static ITS_FeatureRec alarmFeature =
{
    &hmiFeature,                                        /* next */
    &workerFactoryFeature,                              /* prev */
    (ITS_Class)&itsALARM_ClassRec                       /* class */
};
static ITS_FeatureRec hmiFeature =
{
    NULL,                                               /* next */
    &alarmFeature,                                      /* prev */
    (ITS_Class)&itsHMI_ClassRec                         /* class */
};
#endif


ITS_Feature ITS_FeatureListHead = &applicationFeature;
#if defined(STANDALONE)
ITS_Feature ITS_FeatureListTail = &timersFeature;
#else
ITS_Feature ITS_FeatureListTail = &hmiFeature;
#endif
