
#include <its_dlsym.h>

int
main(int argc, char **argv)
{
    DLSYM_Manager *m;
    int ret;
    int (*func)();
    int *sym;

    m = DLSYM_Create();

    printf("Load returns %d\n", ret = DLSYM_Load(m, "testdll.dll"));
    printf("Handle %08x\n", m->handle);

    if (ret == ITS_SUCCESS)
    {
        printf("Search 1 returns %08x\n", func = (int (*)())DLSYM_Resolve(m, "TestDispatchFunc"));
        printf("Call returns %d\n", (*func)());

        printf("Search 2 returns %08x\n", sym = DLSYM_Resolve(m, "TestDispatchInt"));
        printf("Deref returns %d\n", *sym);
        DLSYM_Unload(m);
    }

    DLSYM_Destroy(m);

    return (0);
}
