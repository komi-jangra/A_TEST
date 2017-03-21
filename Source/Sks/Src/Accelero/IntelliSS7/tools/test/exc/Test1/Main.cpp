////////////////////////////////////////////////////////////////////////////////
//
// Test1.
//
////////////////////////////////////////////////////////////////////////////////

//
// On NT, at the end of the test also check the NT Event Log.
//

#include <iostream>
#include <conio.h>

#include <its_exception.h>
#include <Test1Exception.h>


using namespace std;
using namespace its;



static void Test1();
static void Test2();


int main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;

    try
    {
        Test1();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        exp.Log();
    }

    try
    {
        Test2();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        exp.Log();
    }


    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();

    return 0;
}


void Test1()
{
    int i = 0;

    i++;

    throw TEST1_Exception1("Hello Exc...", 1999);
}


void Test2()
{
    int i = 0;

    i++;

    throw TEST1_Exception2("Hello Exc...", "(Re)Hello Exc...", 13, 1999, 2001);
}

