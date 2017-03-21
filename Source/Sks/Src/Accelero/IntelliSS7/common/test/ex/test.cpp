////////////////////////////////////////////////////////////////////////////////
//
// Exception unit tester - how to use example.
//
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <conio.h>

#include <its_event_log.h>
#include <its_exception_log.h>
#include <its_exception.h>


#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif    // defined(ITS_NAMESPACE)


// Forward declarations.
void TestNoThrow();
void TestThrow();


int main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;

    try
    {
        ITS_NtEventLog::RegistryRemoveSource("ITS");

        ITS_NtEventLog::RegistryCreateSource("ITS", "ItsMsgFile.dll");

        TestNoThrow();

        TestThrow();
    }
    catch (ITS_GenericException& exp)
    {
        cout << exp.GetDescription() << endl;

        exp.Log();
    }
    catch (exception& exp)
    {
        cout << exp.what() << endl;  
    }


    try
    {
        ITS_NtEventLog::RegistryRemoveSource("WSS MSC");

        ITS_NtEventLog::RegistryCreateSource("WSS MSC", "ItsMsgFile.dll");

        static ITS_NtExceptionLog exceptionLog("WSS MSC");

        ITS_GenericException::SetExceptionLog(exceptionLog);

        TestNoThrow();

        TestThrow();
    }
    catch (ITS_GenericException& exp)
    {
        cout << exp.GetDescription() << endl;

        exp.Log();
    }
    catch (exception& exp)
    {
        cout << exp.what() << endl;  
    }


    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();

    return 0;
}


void TestNoThrow()
{
    char c;

    char array[20];

    int foo;

    double ert;

    int* ptr;


    foo = foo++;



    ITS_ASSERT(false);

}

void TestThrow()
{

    ITS_THROW_ASSERT(false);

}