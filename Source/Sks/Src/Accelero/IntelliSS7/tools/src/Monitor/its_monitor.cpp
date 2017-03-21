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
//  ID: $Id: its_monitor.cpp,v 1.1.1.1 2007-10-08 11:12:04 bsccs2 Exp $
//
//  LOG: $Log: not supported by cvs2svn $
//  LOG: Revision 1.1.1.1  2007/10/04 13:24:39  bsccs2
//  LOG: init tree
//  LOG:
//  LOG: Revision 1.1.1.1  2007/08/03 06:49:18  cvsadmin
//  LOG: BscCs2
//  LOG:
//  LOG: Revision 1.1.1.1  2007/03/08 15:14:34  cvsadmin
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
//  LOG: Revision 2.0  1999/12/03 23:29:42  mmiers
//  LOG:
//  LOG: Begin third iteration.
//  LOG:
//  LOG: Revision 1.2  1999/09/10 19:42:58  rsonak
//  LOG:
//  LOG: Added grouping logic
//  LOG:
//  LOG: Revision 1.1  1999/09/10 17:34:45  rsonak
//  LOG:
//  LOG: Process Monitoring utility
//  LOG:
//  LOG: Revision 1.10  1999/09/10 17:18:06  rsonak
//  LOG:
//  LOG: duh
//  LOG:
//  LOG: Revision 1.9  1999/09/10 17:16:20  rsonak
//  LOG:
//  LOG: Added cvs logs
//  LOG:
//  LOG: Revision 1.1  1999/09/07 20:22:03  rsonak
//  LOG:
// 
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <winbase.h>

#include <crtdbg.h>

#include <its_event_log.h>
#include <its_exception_log.h>
#include <its_exception.h>
#include <its_app.h>

#include <its_stubs.h>
#include <its_ss7_stubs.h>

#include <its_monitor.h>
#include <fstream>

char *startupFileName     = "its_monitor.dat";

#define MAX_TASKS                       32

#define MONITOR_PERIOD                  3000

MonitorObject *pMonitorObject[MAX_TASKS];
int numMonitorObjects = 0;

int
MonitorService::StartTask(MonitorObject *pTask)
{
    STARTUPINFO si;
    memset (&si, 0, sizeof STARTUPINFO);

    if (pTask->nShowFlag != SW_SHOWNORMAL)
    {
        si.dwFlags |= STARTF_USESHOWWINDOW;
        si.wShowWindow = pTask->nShowFlag;
    }
    
    si.lpTitle = pTask->title;
    si.lpDesktop = "WinSta0\\Default";
    
    PROCESS_INFORMATION pi;
    memset (&pi, 0, sizeof PROCESS_INFORMATION);
    
    return CreateProcess(NULL, pTask->taskName, NULL, NULL, TRUE, 
             CREATE_NEW_CONSOLE, GetEnvironmentStrings(), pTask->dirName, 
             &si, &pi);
}

HWND
MonitorService::FindTaskWin (char *pTitle)
{
    char    buf[200];
    HWND    hwnd;

    // First, try the normal window title
    if (hwnd = FindWindow (NULL, pTitle))
    {
        return (hwnd);
    }

    // If not found, try "Select" and the title
    sprintf (buf, "Select %s", pTitle);
    if (hwnd = FindWindow (NULL, buf))
    {
        return (hwnd);
    }

    // If not found, try "Mark" and the title
    sprintf (buf, "Mark %s", pTitle);
    if (hwnd = FindWindow (NULL, buf))
    {
        return (hwnd);
    }

    // OK, give up
    return (NULL);
}

void
MonitorService::StopTask(MonitorObject *pTask)
{
    HWND hwnd;
    if (hwnd = FindTaskWin (pTask->title))
    {
        ::SendMessage(hwnd, WM_CLOSE, 0, 0);
    }
}

void
MonitorService::StartTasks()
{
    char filePath[MAX_PATH];
    char *temp;
    temp = getenv("ITS_MONITOR_PATH");

    if (temp)
    {
        LogEvent("Got Env variable", ITS_EventLog::LOG_INFORMATION_TYPE);  
        
        strcpy(filePath, temp);

        if (temp[strlen(temp) - 1] != '\\')
        {
            strcat(filePath, "\\");
        }

        strcat(filePath, startupFileName);
    }
    else
    {
        LogEvent("Did not get Env variable", ITS_EventLog::LOG_INFORMATION_TYPE);  
        
        strcpy(filePath, startupFileName);//By default, it takes from c:\winnt\system32
    }

    LogEvent("Starting Tasks", ITS_EventLog::LOG_INFORMATION_TYPE);                

    LogEvent("Opening file", ITS_EventLog::LOG_INFORMATION_TYPE);                

    FILE *fp = fopen(filePath, "r");
    if (!fp)
    {
        LogEvent(filePath, ITS_EventLog::LOG_INFORMATION_TYPE);    
        LogEvent("File could not be opened", ITS_EventLog::LOG_INFORMATION_TYPE);    
        return;
    }        

    LogEvent("Opened file", ITS_EventLog::LOG_INFORMATION_TYPE);    

    char buffer[1024];            

    while (!IsServiceStopped() && fgets(buffer, 256, fp))
    {
        buffer[strlen(buffer) - 1] = 0;

        if (!strnicmp(buffer, "task", strlen("task")))
        {
            if (numMonitorObjects == MAX_TASKS - 1)
            {
                LogEvent("Too many tasks", ITS_EventLog::LOG_ERROR_TYPE);
                break;
            }

            pMonitorObject[numMonitorObjects] = (MonitorObject *) malloc(sizeof(MonitorObject));

            if (pMonitorObject == NULL)
            {
                LogEvent("No memory", ITS_EventLog::LOG_ERROR_TYPE);                
                break;
            }

            memset(pMonitorObject[numMonitorObjects], 0, sizeof(MonitorObject));
            pMonitorObject[numMonitorObjects]->nShowFlag = SW_SHOWNORMAL;

            strcpy(pMonitorObject[numMonitorObjects]->title, buffer + strlen("task") + 1);

        }
        if (!strnicmp(buffer, "sleep", strlen("sleep")))
        {
            ITS_UINT sleep_time;
            sscanf(buffer + strlen ("sleep") + 1, "%d", &sleep_time);

            if (pMonitorObject[numMonitorObjects])
                pMonitorObject[numMonitorObjects]->nSleep = sleep_time;

            Sleep(sleep_time * 1000);
        }
        else if (!strnicmp(buffer, "group", strlen("group")))
        {
            sscanf(buffer + strlen ("group") + 1, "%d", &pMonitorObject[numMonitorObjects]->nGroup);
        }
        else if (!strnicmp(buffer, "directory", strlen("directory")))
        {
            ExpandEnvironmentStrings (buffer + strlen("directory") + 1, pMonitorObject[numMonitorObjects]->dirName, MAX_PATH);
        }
        else if (!strnicmp(buffer, "hide", strlen("hide")))
        {
            pMonitorObject[numMonitorObjects]->nShowFlag = SW_HIDE;
        }
        else if (!strnicmp(buffer, "minimize", strlen("minimize")))
        {
            pMonitorObject[numMonitorObjects]->nShowFlag = SW_MINIMIZE;
        }
        else if (!strnicmp(buffer, "maximize", strlen("maximize")))
        {
            pMonitorObject[numMonitorObjects]->nShowFlag = SW_MAXIMIZE;
        }
        else if (!strnicmp(buffer, "no restart", strlen("no restart")))
        {
            pMonitorObject[numMonitorObjects]->bNoRestart = TRUE;
        }
        else if (!strnicmp(buffer, "no start", strlen("no start")))
        {
            pMonitorObject[numMonitorObjects]->bNoStart = TRUE;
            numMonitorObjects++;
        }
        else if (!strnicmp(buffer, "run", strlen("run")))
        {
            ExpandEnvironmentStrings(buffer + strlen("run") + 1, 
                           pMonitorObject[numMonitorObjects]->taskName, MAX_PATH);

            BOOL res = StartTask(pMonitorObject[numMonitorObjects]);

            sprintf (buffer, "%s Started %s Directory %s result %d\n", 
                     pMonitorObject[numMonitorObjects]->title, 
                     pMonitorObject[numMonitorObjects]->taskName, 
                     pMonitorObject[numMonitorObjects]->dirName, res);

            printf (buffer);

            LogEvent("Task started", ITS_EventLog::LOG_INFORMATION_TYPE);

            pMonitorObject[numMonitorObjects]->bStarted     = TRUE;
            numMonitorObjects++;
        }
    }
    fclose(fp);
}

void
MonitorService::MonitorTasks()
{
    for (ITS_UINT i = 0; i < numMonitorObjects; i++)
    {
        if (pMonitorObject[i]->bNoRestart)
        {
            continue;
        }

        if (!FindTaskWin (pMonitorObject[i]->title))
        {
            ITS_USHORT nGroup;
            char buf[80];

            if ((!pMonitorObject[i]->bStarted))
            {
                continue;
            }

            nGroup = pMonitorObject[i]->nGroup;
            if (nGroup)
            {
                sprintf(buf, "%s Group %d", pMonitorObject[i]->title, nGroup);
            }
            else
            {
                strcpy(buf, pMonitorObject[i]->title);
            }

            // Log that service is started.

            LogEvent("V7M started", ITS_EventLog::LOG_INFORMATION_TYPE);

            // If the task did not belong to any group just restart it
            if (!nGroup)
            {
                if (!pMonitorObject[i]->bNoStart)
                {
                    StartTask(pMonitorObject[i]);
                }

                continue;
            }

            // Kill members of the same group
            for (ITS_UINT j = 0; j < numMonitorObjects; j++)
            {
                if ((j != i) && (pMonitorObject[j]->nGroup == nGroup))
                {
                    StopTask(pMonitorObject[j]);
                }
            }

            // Allow NT 10 sec to finish dirty work
            Sleep(10000);

            // Restart the group
            for (j = 0; j < numMonitorObjects; j++)
            {
                if (pMonitorObject[j]->nGroup == nGroup)
                {
                    if (!pMonitorObject[j]->bNoStart)
                    {
                        StartTask(pMonitorObject[j]);
                    }
                    else
                    {
                        pMonitorObject[i]->bStarted = FALSE;
                    }

                    if (pMonitorObject[j]->nSleep)
                    {
                        Sleep(pMonitorObject[j]->nSleep * 1000);
                    }
                }
            }
            // Next task/group will be restarted next monitor period
            break;
        }
        else
        {
            // Window found. Mark as started
            pMonitorObject[i]->bStarted = TRUE;
        }
    }
}

void
MonitorService::LogEvent(LPTSTR infoString, ITS_EventLog::EventType eventType)
{
    string infoStarted;
    infoStarted.append(GetDisplayedName());
    infoStarted.append(infoString);

    GetEventLog().Log(infoStarted, eventType);
}

void 
MonitorService::Run(int argc, const char** argv)
{
    if (applicationType == AT_SERVICE)
    {        
        for (ITS_UINT i = 0; i < MAX_TASKS; i++)
        {
            pMonitorObject[i] = 0;
        }

        numMonitorObjects = 0;

        LogEvent("Env being read", ITS_EventLog::LOG_INFORMATION_TYPE);

        FILE* fpTemp = fopen("env.txt", "w");

        LPTSTR lpszVariable; 
        LPVOID lpvEnv; 
 
        // Get a pointer to the environment block. 
 
        lpvEnv = GetEnvironmentStrings(); 
 
        // Variable strings are separated by NULL byte, and the block is 
        // terminated by a NULL byte. 
 
        for (lpszVariable = (LPTSTR) lpvEnv; *lpszVariable; lpszVariable++) 
        { 
           while (*lpszVariable) 
           {
              fputc(*lpszVariable++, fpTemp); 
           }

           fputc('\n', fpTemp); 
        } 

        fclose(fpTemp);

        LogEvent("Monitor Service being run", ITS_EventLog::LOG_INFORMATION_TYPE);

        SetStatus(SERVICE_RUNNING, 0);

        //First start the task
        StartTasks();

        // To tell the SCM that the service is now started.
//        SetStatus(SERVICE_RUNNING, 0);

        // Log that service is started.

        LogEvent("Monitor Service started", ITS_EventLog::LOG_INFORMATION_TYPE);
    }

    BeforeApplicationLoop(argc, argv);

    while (!IsServiceStopped())
    {
        ApplicationLoop();

        DWORD res = WaitForSingleObject(
                                stopEventHandle,  // Handle.
                                MONITOR_PERIOD);              

        switch (res)
        {
            case WAIT_OBJECT_0:
                break;

            case WAIT_TIMEOUT:            
                MonitorTasks();
                break;

            default:
                SetServiceStopped();
                break;
        }        
    }

    AfterApplicationLoop();

    if (applicationType == AT_SERVICE)
    {
        // Log that service is stopped.

        LogEvent("Service stopped", ITS_EventLog::LOG_INFORMATION_TYPE);

        // To tell the SCM that the service is now stopped.

        SetStatus(SERVICE_STOPPED, 0);
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  MonitorService::BeforeApplicationLoop.
//

void MonitorService::BeforeApplicationLoop(int argc, const char** argv)
{
    ////////////////////////////////////////////////////////
    // Mandatory initializations.
    ////////////////////////////////////////////////////////

}


////////////////////////////////////////////////////////////////////////////////
//
//  MonitorService::ApplicationLoop.
//
void MonitorService::ApplicationLoop()
{

}


////////////////////////////////////////////////////////////////////////////////
//
//  MonitorService::AfterApplicationLoop.
//

void MonitorService::AfterApplicationLoop()
{
    for (ITS_UINT i = 0; i < numMonitorObjects; i++)
    {
        if (pMonitorObject[i])
        {
            free(pMonitorObject[i]);
        }
    }
}

//.implementation:public
////////////////////////////////////////////////////////////////////////////////
//
//  Purpose:
//      Install the service in the Service Control Manager database.
//
//  Input Parameters:
//      None.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.       
//
//  Notes:
//      Usually indirectly called by the installation procedure or from the 
//      command line.
//
//  See Also:
//
////////////////////////////////////////////////////////////////////////////////
void 
MonitorService::Install()
{
    try
    {        
        SC_HANDLE hService = NULL;
        SC_HANDLE hSCM     = NULL;

        char path[BUFSIZ];

        DWORD resLength = ::GetModuleFileName(NULL, path, BUFSIZ);

        if (resLength == 0)
        {
            ITS_THROW_WIN32_ERROR(::GetLastError());
        }

        LogEvent("Monitor Service being created", ITS_EventLog::LOG_INFORMATION_TYPE);

        hSCM = ::OpenSCManager(
                    NULL,                   // Machine (NULL == local).
                    NULL,                   // Database (NULL == default).
                    SC_MANAGER_ALL_ACCESS); // Access required.

        if (hSCM == NULL)
        {
            ITS_THROW_WIN32_ERROR(::GetLastError());
        }

        hService = ::CreateService(
                        hSCM,                        // SCM.
                        GetInternalName().c_str(),   // Service name.
                        GetDisplayedName().c_str(),  // Service displayed name.
                        SERVICE_ALL_ACCESS,          // Desired access.
                        SERVICE_INTERACTIVE_PROCESS, // Service type.
                        SERVICE_DEMAND_START,        // Start type.
                        SERVICE_ERROR_NORMAL,        // Error control type.
                        path,                        // Service's binary.
                        NULL,                        // No load ordering group.
                        NULL,                        // No tag identifier.
                        GetDependencies().c_str(),   // Dependencies.
                        NULL,                        // LocalSystem account.
                        NULL);                       // No password.


        if (hService == NULL)
        {
            ITS_THROW_WIN32_ERROR(::GetLastError());
        }

        // Service has been successfully installed.

        LogEvent("Monitor Service created", ITS_EventLog::LOG_INFORMATION_TYPE);


        BOOL bRes = ::CloseServiceHandle(hService);

        if (!bRes)
        {
            ITS_THROW_WIN32_ERROR(::GetLastError());
        }

        bRes = ::CloseServiceHandle(hSCM);

        if (!bRes)
        {
            ITS_THROW_WIN32_ERROR(::GetLastError());
        }
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();
    }
    catch (exception& exc)
    {
        const char* what = exc.what();
    }
#if defined(NDEBUG)
    catch (...)
    {
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
//  Entry point.
//

void main(int argc, const char** argv)
{
    try
    {

        // 
        // The exception log and event log objects
        // MUST always be created as static objects.
        //
    
        static ITS_NtExceptionLog exceptionLog("ITS_Monitor");
        static ITS_NtEventLog eventLog("ITS_Monitor");

        // Ideally, the following should be done by
        // the installation procedure.

        //ITS_NtEventLog::RegistryCreateSource("Monitor", "ItsMsgFile.dll");
    
        // Set the exception log.

        //ITS_GenericException::SetExceptionLog(exceptionLog);

        //
        // Set IntelliSS7 Application name.
        //

        ITS_Application::SetName("ITS_Monitor");

        // Create the unique service object.

        MonitorService service("ITS_Monitor", "ITS_Monitor", exceptionLog, eventLog);

        // Process the command line.

        service.ProcessCommandLine(argc, argv);

        //service.SetApplicationType(ITS_Service::AT_CONSOLE_APPLICATION);
        service.SetApplicationType(ITS_Service::AT_SERVICE);

       
        if (service.GetApplicationType() == ITS_Service::AT_SERVICE)
        {
            service.RunAsService();
        }
        else if (service.GetApplicationType() ==
                 ITS_Service::AT_CONSOLE_APPLICATION)
        {
            service.RunAsConsoleApplication(argc, argv);
        }
    }
    catch (exception& exc)
    {
        exc = exc;
        exit(EXIT_FAILURE);
    }

#if !defined(_DEBUG)

    catch (...)
    {
        exit(EXIT_FAILURE);
    }

#endif  // !defined(_DEBUG)

}

