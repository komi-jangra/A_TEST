
#include <windows.h>
#include <stdio.h>

__declspec(dllexport) int
bar()
{
    return 42;
}

int
main(int argc, char **arg)
{
    HANDLE lib, lib2;
    int (*func)();

    lib = LoadLibrary("Debug/testdll.dll");
    lib2 = LoadLibrary("Debug/testdll2.dll");

    func = (int (*)())GetProcAddress(lib2, "TestDispatchFunc2");

    printf("func %p returns %d\n", func, (*func)());

    FreeLibrary(lib);
}
