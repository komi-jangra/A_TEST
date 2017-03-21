////////////////////////////////////////////////////////////////////////////////
//
// Test7.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)
#pragma warning(disable:4786) 
#endif // defined(WIN32)

#include <iostream>
#include <conio.h>

#include <its++.h>

#include <test7_1_authentication_directive_rrl.h>
#include <test7_1_authentication_failure_report_rrl.h>
#include <test7_1_bar_bar1.h>
#include <test7_1_bar_bar2.h>
#include <test7_1_foo3.h>
#include <test7_1_foo4.h>
#include <test7_2_feature_request_rrl.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)



static bool testPrint = true;


int main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;

    try
    {
        int res = ITS_GlobalStart(0);

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__);
        }

        // TODO: to be implemented.

        ITS_GlobalStop();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();
    }

    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();

    return 0;
}

