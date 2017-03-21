// testdll.cpp : Defines the entry point for the DLL application.
//

#include "testdll.h"
#include "testdll2.h"

// This is an example of an exported function.
TESTDLL2_API int TestDispatchFunc2(void)
{
    return TestDispatchFunc();
}
