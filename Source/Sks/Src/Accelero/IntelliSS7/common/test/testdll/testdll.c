// testdll.cpp : Defines the entry point for the DLL application.
//

#include "testdll.h"
#include "testdll2.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	    break;
    }

    return TRUE;
}


// This is an example of an exported variable
TESTDLL_API int TestDispatchInt = 300;

__declspec(dllimport) int bar();

// This is an example of an exported function.
TESTDLL_API int TestDispatchFunc(void)
{
    return bar();
}
