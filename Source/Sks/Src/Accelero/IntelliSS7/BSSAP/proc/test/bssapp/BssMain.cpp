#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>


#include <engine++.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif


static void Usage(const char** args)
{
    cout << " Usage: " << args[0] << endl;
    cout << " ConfigFileName <configFile> " << endl;
    cout << endl;
    exit (0);
}


int
ParseArguments(int argc, const char** args)
{
    int i = 1;
    int flag = 1;
    int ret = 0;

    if (argc == 1)
    {
        Usage (args);
        return -1; 
    }

    for(; i < argc && flag; i++)
    {
        if(strcmp(args[i], "-configFile") == 0)
        {
           flag = 0;
        }
        else
        {
           Usage(args);
        }
    }

    /* from here onwards are engine arguments. */
    return (i - 2);
}


int
main(int argc, const char **args)
{
    int ret;

    ret = ParseArguments(argc, args);

    ENGINE_Initialize((argc - ret), &args[ret], NULL, 0);

    ret = ENGINE_Run(argc, args);

    return ret;
}
