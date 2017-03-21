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
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:15  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.2  2003/01/16 19:08:31  mmiers
 * LOG: Warning removal, Borland update.
 * LOG:
 * LOG: Revision 7.1  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.2  2002/08/29 18:31:26  ngoel
 * LOG: add delimitor '|' after line number
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.7  2002/07/05 19:33:59  yranade
 * LOG: Fix flag handling for IP transports.  Warning removal.
 * LOG:
 * LOG: Revision 6.6  2002/06/13 20:45:01  mmiers
 * LOG: Range checking
 * LOG:
 * LOG: Revision 6.5  2002/05/07 16:23:29  mmiers
 * LOG: Change field separator
 * LOG:
 * LOG: Revision 6.4  2002/05/07 15:58:27  wweng
 * LOG: Add extra fields to format.
 * LOG:
 * LOG: Revision 6.3  2002/03/01 23:12:56  mmiers
 * LOG: Pegs and alarms
 * LOG:
 * LOG: Revision 6.2  2002/02/28 23:32:46  mmiers
 * LOG: Add to alarm API.  Add peg API.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/11/19 16:02:23  mmiers
 * LOG: Wrong thread id.
 * LOG:
 * LOG: Revision 5.2  2001/09/04 16:16:37  mmiers
 * LOG: Move alarm event to callData.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:10  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.5  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.4  2001/05/09 22:21:31  mmiers
 * LOG: Updates after ADP brainstorming.
 * LOG:
 * LOG: Revision 4.3  2001/05/02 00:01:51  mmiers
 * LOG: Finish alarm implementation.  HMI just needs the monitor
 * LOG: algorithm.
 * LOG:
 * LOG: Revision 4.2  2001/05/01 23:09:03  mmiers
 * LOG: Add functionality for HMI and alarm.  The rest is pretty easy.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_alarm.h>
#include <its_timers.h>
#include <its_assertion.h>

#ident "$Id: its_alarms.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*
 * extern
 */
ITSDLLAPI CALLBACK_Manager *ALARM_Callbacks = NULL;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an alarm
 *
 *  Input Parameters:
 *      text - the text you want to send.
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
ALARM_Send(ITS_Class objClass, ITS_OCTET *bytes, ITS_UINT len)
{
    ITS_C_ASSERT(ALARM_CLASS_SEND(objClass) != NULL);

    ALARM_CLASS_SEND(objClass)(bytes, len);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Issue a formatted alarm.
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
 *      Usage: ALARM_IssueAlarm(&myAlarmFormat, __FILE__, __LINE__,
 *                              "some format for this error: %d", myError);
 *
 ****************************************************************************/
ITSDLLAPI void
ALARM_IssueAlarm(ITS_Class alarmClass, ALARM_Format *alarm,
                 const char *file, const int line,
                 const char *format, ...)
{
    va_list alist;

    va_start(alist, format);

    ALARM_VIssueAlarm(alarmClass, alarm, file, line, format, alist);

    va_end(alist);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Issue a formatted alarm.
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
ALARM_VIssueAlarm(ITS_Class alarmClass, ALARM_Format *alarm,
                  const char *file, const int line,
                  const char *format, va_list alist)
{
    char buf[ITS_PATH_MAX << 1], *tmp;
    int ret;
    ITS_TIME curTime;

    ITS_C_ASSERT(alarm != NULL);

    curTime = TIMERS_Time();

    if (!alarm->gate || curTime > alarm->last)
    {
        alarm->last = curTime + alarm->reset;

        ret = sprintf(buf, "%d|%s|%d|%s|%s|%s|%s|%d",
                      alarm->id, alarm->subsys, alarm->severity,
                      alarm->object, alarm->desc,
                      file, alarm->func, line);

        if (ret > 0)
        {
            tmp = buf + strlen(buf);

            if (format)
            {
                strcat(tmp, "|");
                tmp++;
                vsprintf(tmp, format, alist);
            }
        }

        ITS_C_ASSERT(strlen(buf) < (ITS_PATH_MAX << 1));
        
        ALARM_Send(alarmClass, (ITS_OCTET *)buf, strlen(buf));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the ALARM subsystem to a ready state.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    /* create callback manager */
    if ((ALARM_Callbacks = CALLBACK_InitManager()) == NULL)
    {
        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the ALARM subystem.
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
ClassTerminate(ITS_Class objClass)
{
    /* delete callback manager */
    CALLBACK_DestroyManager(ALARM_Callbacks);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Default alarm handler
 *
 *  Input Parameters:
 *      text - the text you want to send.
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
AlarmSend(ITS_OCTET *bytes, ITS_UINT len)
{
    ITS_EVENT ev;

    ITS_EVENT_INIT(&ev, ITS_NO_SRC, (ITS_USHORT)len);

    memcpy(ev.data, bytes, len);

    CALLBACK_CallCallbackList(ALARM_Callbacks,
                              NULL,
                              (ITS_POINTER)&ev);

    ITS_EVENT_TERM(&ev);
}

/*
 * the class record
 */
ITSDLLAPI ALARM_ClassRec itsALARMS_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        ALARMS_CLASS_NAME,              /* class name */
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
    },
    /* alarm part */
    {
        AlarmSend
    }
};

ITSDLLAPI ITS_Class itsALARM_Class = (ITS_Class)&itsALARMS_ClassRec;
