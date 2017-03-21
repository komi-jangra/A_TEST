////////////////////////////////////////////////////////////////////////////////
//
// Test11.
//
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <conio.h>

#include <its++.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)





int main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;


    cout << "End of test..." << endl;
    
    // To stop here in console application.

    cout << "Type any key to quit...";

    char c = getch();

    return EXIT_SUCCESS;
}
