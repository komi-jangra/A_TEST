
// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TESTDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TESTDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTDLL2_EXPORTS
#define TESTDLL2_API __declspec(dllexport)
#else
#define TESTDLL2_API __declspec(dllimport)
#endif

TESTDLL2_API int TestDispatchFunc2(void);

