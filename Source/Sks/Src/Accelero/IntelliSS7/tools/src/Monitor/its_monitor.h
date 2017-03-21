////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: IntelliSS7                                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: its_monitor.h,v 1.1.1.1 2007-10-08 11:12:04 bsccs2 Exp $
//
//  LOG: $Log: not supported by cvs2svn $
//  LOG: Revision 1.1.1.1  2007/10/04 13:24:39  bsccs2
//  LOG: init tree
//  LOG:
//  LOG: Revision 1.1.1.1  2007/08/03 06:49:18  cvsadmin
//  LOG: BscCs2
//  LOG:
//  LOG: Revision 1.1.1.1  2007/03/08 15:14:35  cvsadmin
//  LOG: BSC project
//  LOG:
//  LOG: Revision 9.1  2005/03/23 12:54:07  cvsadmin
//  LOG: Begin PR6.5
//  LOG:
//  LOG: Revision 8.2  2005/03/21 13:52:48  cvsadmin
//  LOG: PR6.4.2 Source Propagated to Current
//  LOG:
//  LOG: Revision 7.1  2002/08/26 22:10:17  mmiers
//  LOG: Begin PR6.2
//  LOG:
//  LOG: Revision 6.1  2002/02/28 16:14:30  mmiers
//  LOG: Begin PR7.
//  LOG:
//  LOG: Revision 5.1  2001/08/16 20:46:19  mmiers
//  LOG: Start PR6.
//  LOG:
//  LOG: Revision 4.1  2001/05/01 00:53:22  mmiers
//  LOG: Begin PR5
//  LOG:
//  LOG: Revision 3.1  2000/08/16 00:07:07  mmiers
//  LOG:
//  LOG: Begin round 4.
//  LOG:
//  LOG: Revision 2.0  1999/12/03 23:29:43  mmiers
//  LOG:
//  LOG: Begin third iteration.
//  LOG:
//  LOG: Revision 1.1  1999/09/10 17:34:46  rsonak
//  LOG:
//  LOG: Process Monitoring utility
//  LOG:
//  LOG: Revision 1.6  1999/09/10 17:18:06  rsonak
//  LOG:
//  LOG: duh
//  LOG:
//  LOG: Revision 1.5  1999/09/10 17:16:21  rsonak
//  LOG:
//  LOG: Added cvs logs
//  LOG:
//  LOG: Revision 1.1  1999/09/07 20:22:03  rsonak
//  LOG:
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  MonitorService.
//

#include <iostream>
#include <string>
#include <its++.h>
#include <its_service.h>

using namespace std;
using namespace its;

struct MonitorObject
{
#define MAX_TITLE_LEN   MAX_PATH
    char title[MAX_TITLE_LEN];        // Title of the task for monitoring
    char taskName[MAX_PATH];          // Task name
    char dirName[MAX_PATH];           // Current directory for the task
    ITS_USHORT nGroup;                // Goup to which task belongs or zero
    ITS_USHORT nSleep;                // Sleep period before task is started
    bool bNoRestart;                  // If TRUE Task is not been monitored or restarted
    bool bNoStart;                    // If TRUE Task is only monitored, used to kill group members
    ITS_USHORT nShowFlag;
    bool bStarted;                    // If TRUE, task was started
};


class MonitorService : public ITS_Service
{
public:
    
    MonitorService(const string& displayedName,
                   const string& internalName,
                   ITS_ExceptionLog& exceptionLogParam,
                   ITS_EventLog& eventLogParam)
    :   ITS_Service(displayedName, internalName,
                    exceptionLogParam, eventLogParam)
    {};

    virtual ~MonitorService()
    {
        // Nothing to do.
    };

protected:

    virtual void        BeforeApplicationLoop(int argc, const char** argv);

    virtual void        ApplicationLoop();

    virtual void        AfterApplicationLoop();

    virtual void        LogEvent(LPTSTR infoString, ITS_EventLog::EventType eventType);

    virtual void        Run(int argc, const char** argv);

    void Install();

    int StartTask(MonitorObject *pTask);

    void StartTasks();

    HWND FindTaskWin (char *pTitle);

    void StopTask(MonitorObject *pTask);

    void MonitorTasks();

};

