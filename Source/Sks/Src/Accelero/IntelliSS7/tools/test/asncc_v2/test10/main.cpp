////////////////////////////////////////////////////////////////////////////////
//
// Test10.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)
#pragma warning(disable:4786) 
#endif // defined(WIN32)

#include <iostream>
#include <conio.h>

#include <its++.h>
#include <its_ss7_stubs.h>

#include <map_v2_teleservice_code.h>
#include <map_v2_teleservice_list.h>
#include <map_v4_teleservice_code.h>
#include <map_v4_teleservice_list.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace map_v2;
using namespace map_v4;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)


static void TestLRF();

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



void TestLRF()
{
    vector<byte> vect1;

    vect1.push_back(0x01U);

    map_v2::TeleserviceCode* teleserviceCode1 = 
        new map_v2::TeleserviceCode(vect1);

    map_v2::TeleserviceList* teleserviceList1 = 
        new map_v2::TeleserviceList();

    teleserviceList1->AddElement(teleserviceCode1);

    delete teleserviceList1;



    vector<byte> vect2;

    vect1.push_back(0x02U);

    map_v4::TeleserviceCode* teleserviceCode2 = 
        new map_v4::TeleserviceCode(vect2);  

    map_v4::TeleserviceList* teleserviceList2 = 
        new map_v4::TeleserviceList();

    teleserviceList2->AddElement(teleserviceCode2);

    delete teleserviceList2;
}
