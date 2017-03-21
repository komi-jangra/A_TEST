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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.8.1  2004/03/18 14:02:34  kannanp
 * LOG: Added macro ALARM_LVL_CLEAR.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/02/18 23:48:00  randresol
 * LOG: Add macro ALARM_LEVEL_TO_TEXT
 * LOG:
 * LOG: Revision 7.3  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:18:33  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/05/08 18:28:21  mmiers
 * LOG: Add off alarm level.
 * LOG:
 * LOG: Revision 6.3  2002/03/01 23:12:56  mmiers
 * LOG: Pegs and alarms
 * LOG:
 * LOG: Revision 6.2  2002/02/28 23:29:04  mmiers
 * LOG: Add to alarm API, add peg API.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:12  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/05/09 22:21:31  mmiers
 * LOG: Updates after ADP brainstorming.
 * LOG:
 * LOG: Revision 4.2  2001/05/01 23:09:03  mmiers
 * LOG: Add functionality for HMI and alarm.  The rest is pretty easy.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_ALARM_H)
#define ITS_ALARM_H

#include <stdarg.h>

#include <its.h>
#include <its_callback.h>

#ident "$Id: its_alarm.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:ALARM_
 *****************************************************************************
 *  Interface:
 *      ALARM_*
 *
 *  Purpose:
 *
 *  Usage:
 *
 *****************************************************************************/

typedef void (*AlarmSendProc)(ITS_OCTET *bytes, ITS_UINT len);

typedef struct
{
    AlarmSendProc   alarmSend;
}
ALARM_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    ALARM_ClassPart     alarmClass;
}
ALARM_ClassRec;

#define ALARM_CLASS_SEND(cl) \
    (((ALARM_ClassRec *)(cl))->alarmClass.alarmSend)

#define ALARMS_CLASS_NAME   "Alarm Base Class"
#define ALARM_CLASS_NAME    "Alarm Class"

ITSDLLAPI extern ALARM_ClassRec   itsALARMS_ClassRec;
ITSDLLAPI extern ALARM_ClassRec   itsALARM_ClassRec;

ITSDLLAPI extern ITS_Class        itsALARM_Class;

/*
 * user hook.
 */
ITSDLLAPI extern CALLBACK_Manager *ALARM_Callbacks;

/*
 * API
 */
ITSDLLAPI void ALARM_Send(ITS_Class objClass, ITS_OCTET *bytes, ITS_UINT len);

/*
 * alarm format (description and elements)
 */
typedef struct
{
    ITS_UINT        id;
    char            *subsys;
    char            *desc;
    char            *func;
    char            *object;
    ITS_UINT        severity;
    ITS_TIME        reset;
    ITS_TIME        last;
    ITS_BOOLEAN     gate;
}
ALARM_Format;

/*
 * alarm levels
 */
#define ALARM_LVL_CRIT          0x01
#define ALARM_LVL_MAJOR         0x02
#define ALARM_LVL_MINOR         0x04
#define ALARM_LVL_INFO          0x08
#define ALARM_LVL_OFF           0x10
#define ALARM_LVL_CLEAR         0x20

#define ALARM_DEF_RESET_INTVL   60

#define ALARM_FORMAT_SUBSYS(s, i, d, l, f, o, g) \
    ALARM_Format ALARM_##s##i =  \
    { (i), #s, (d), (f), (o), (l), ALARM_DEF_RESET_INTVL, (0), (g) }

#define ALARM_LEVEL_TO_TEXT(x) \
    ((x==ALARM_LVL_CRIT)    ? "CRITICAL"   : \
    ((x==ALARM_LVL_MAJOR)   ? "MAJOR"      : \
    ((x==ALARM_LVL_MINOR)   ? "MINOR"      : \
    ((x==ALARM_LVL_INFO)    ? "INFO"       : \
    ((x==ALARM_LVL_CLEAR)   ? "CLEAR"      : \
    "OFF")))))  

ITSDLLAPI void ALARM_IssueAlarm(ITS_Class alarmClass, ALARM_Format *fmt,
                                const char *file, const int line,
                                const char *varFormat, ...);

ITSDLLAPI void ALARM_VIssueAlarm(ITS_Class alarmClass, ALARM_Format *fmt,
                                 const char *file, const int line,
                                 const char *varFormat, va_list alist);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_ALARM_H */
