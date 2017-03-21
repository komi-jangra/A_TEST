////////////////////////////////////////////////////////////////////////////////
//
// NT Service unit tester and how to use example.
//
////////////////////////////////////////////////////////////////////////////////

//
// A simple service to show how to use ITS_Service using inheritance.
//

//
// Also demonstrate that if a thread is still running then stop service
// stop everything, including the running thread (probably call exit?).
//

#include <conio.h>
#include <iostream>

#include <its_exception.h>
#include <its_trace.h>
#include <its_service.h>


#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif    // defined(ITS_NAMESPACE)


class TestService : public ITS_Service
{
public:

    TestService(const std::string& displayedName,
                const std::string& internalName,
                ITS_ExceptionLog& exceptionLog,
                ITS_EventLog& eventLog)
        : ITS_Service(displayedName,
                      internalName,
                      exceptionLog,
                      eventLog),
          workingThreadHandle(NULL)
    {};

    virtual ~TestService()
    {};

protected:

    virtual void BeforeApplicationLoop(int argc, const char** argv)
    {
        // Create the working thread.

        DWORD workingThreadID = 0;
    
        workingThreadHandle = ::CreateThread( 
                                    NULL,
                                    0,
                                    (LPTHREAD_START_ROUTINE)_WorkingThread,
                                    (LPVOID)this,
                                    0,
                                    &workingThreadID);
        
        if (workingThreadHandle == NULL)
        {
            ITS_THROW_WIN32_ERROR(::GetLastError());
        }
    }


private:

    static DWORD WINAPI _WorkingThread(LPVOID lpvThreadParam)
    {
        TestService* current = static_cast<TestService*>(lpvThreadParam);


        while(true)
        {
            Sleep(5000);

            current->GetEventLog().Log("Excuting working thread...",
                                       ITS_EventLog::LOG_INFORMATION_TYPE);
        }

        return 0;
    }
        
    HANDLE workingThreadHandle;
};





int main(int argc, const char** argv)
{
    cout << "Begin test..." << endl;

    //////////////////////////////////////
    // Almost a copy of ITS_Service::Main.
    //////////////////////////////////////

    // 
    // The exception log and event log objects
    // MUST always be created as static objects.
    //

    static ITS_NtExceptionLog exceptionLog("Test Service");
    static ITS_NtEventLog eventLog("Test Service");

    // Ideally, the following should be done by
    // the installation procedure.

    ITS_NtEventLog::RegistryCreateSource("Test Service", "ItsMsgFile.dll");

    
    // Set the exception log.

    ITS_GenericException::SetExceptionLog(exceptionLog);

    try
    {
        // The following is required to use the trace mechanism.
        // If running as a service, then the trace file is
        // created in the directory $(SystemRoot)\system32.

        ITS_TraceLevel serviceTraceLevel("Service", TRACE_TO_FILE_MASK);

        ITS_TraceSubSystem::InitializeTrace();

        serviceTraceLevel.Enable();

        ITS_TraceSubSystem::GetTrace().AddLevel("Service", &serviceTraceLevel);

        ITS_TRACE(("Service", "Executing ITS_Service::Main."));


        // Create the unique service object.

        TestService service("Test Service",
                            "Test_Service",
                            exceptionLog,
                            eventLog);

        // The following line would be required to allow the
        // service to accept pause and continue requests.

        // service.SetControlsAccepted(SERVICE_ACCEPT_PAUSE_CONTINUE);


        // Process the command line.

        service.ProcessCommandLine(argc, argv);


        // If not exited then probably under the control of the SCM
        // (unless if already run as a console application).

        if (service.GetApplicationType() == ITS_Service::NT_SERVICE)
        {
            service.RunAsService();
        }
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();

    }
    catch (...)
    {
        ITS_UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();
    }   


    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();

    return 0;
}

