////////////////////////////////////////////////////////////////////////////////
//
// Test1.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)
#pragma warning(disable:4786) 
#endif // defined(WIN32)

#include <iostream>
#include <conio.h>

#include <its++.h>
#include <its_ss7_stubs.h>

#include <test1_authentication_failure_report_rrl.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)


static void Test();
static void TestSpeedAndMemory();

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

        Test();

        //TestSpeedAndMemory();

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


void Test()
{
    AuthenticationFailureReportRRL*
        authenticationFailureReportRRL = 
            new AuthenticationFailureReportRRL();

    AuthenticationFailureReportRRL::
        DenyAccess*
            denyAccess = 
                new AuthenticationFailureReportRRL::
                    DenyAccess();

    denyAccess->
        SetUnspecified();

    authenticationFailureReportRRL->
        SetDenyAccess(denyAccess);

    byte array1[] = { 0x01U };

    vector<byte> v1(array1, array1 + 1);

    AuthenticationFailureReportRRL::
        AuthenticationAlgorithmVersion*
            authenticationAlgorithmVersion =
                new AuthenticationFailureReportRRL::
                    AuthenticationAlgorithmVersion(v1);

    authenticationFailureReportRRL->
        SetAuthenticationAlgorithmVersion(
            authenticationAlgorithmVersion);

    byte array2[] = { 0xA1U, 0xA2U, 0xA3U, 0xA4U, 0xA5U,
                      0xA6U, 0xA7U };

    vector<byte> v2(array2, array2 + 7);

    AuthenticationFailureReportRRL::
        RandomVariableSSD*
            randomVariableSSD = 
            new AuthenticationFailureReportRRL::
                RandomVariableSSD(v2);
    
    authenticationFailureReportRRL->
        SetRandomVariableSSD(
            randomVariableSSD);


    // Encode to ASN.1.

    Octets* octets = authenticationFailureReportRRL->Encode();

    if (testPrint)
    {
        cout << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << *octets;
        cout << endl;
    }

    // Decode from ASN.1 => suffix "After".
    // For all optionals we should check that they are present
    // with the OptionXXXXXXXX() member functions.

    AuthenticationFailureReportRRL*
        authenticationFailureReportRRLAfter = 
            new AuthenticationFailureReportRRL();

    authenticationFailureReportRRLAfter->Decode(*octets);

    const AuthenticationFailureReportRRL::
        DenyAccess&
            denyAccessAfter =
                authenticationFailureReportRRLAfter->
                    GetDenyAccess();

    const AuthenticationFailureReportRRL::
        AuthenticationAlgorithmVersion&
            authenticationAlgorithmVersionAfter =
                authenticationFailureReportRRLAfter->
                    GetAuthenticationAlgorithmVersion();

    const AuthenticationFailureReportRRL::
        RandomVariableSSD&
            randomVariableSSDAfter = 
                authenticationFailureReportRRLAfter->
                    GetRandomVariableSSD();

    if (testPrint)
    {
        cout << endl;
        cout << "Printing decoded AuthenticationFailureReportRRL..." << endl;
        cout << *authenticationFailureReportRRLAfter;
        cout << endl;
    }

    // Release all the memory.

    delete authenticationFailureReportRRLAfter;
    delete authenticationFailureReportRRL;
    delete octets;
}

void TestSpeedAndMemory()
{
    testPrint = false;

    for (long i = 0; i < 10000l; i++)
    {
       Test();
    }

    testPrint = true;
}

