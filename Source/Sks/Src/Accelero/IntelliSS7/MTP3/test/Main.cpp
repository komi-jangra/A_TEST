#include <engine++.h>
#include <test_const.h>

#include <iostream>
#include "test_const.h"

using namespace its;
using namespace std;

ITS_BOOLEAN recv_mode = ITS_FALSE;

void Usage(const char* var);

APP_MODE appMode;
 
int main(const int argc, const char** argv)
{
    int i = 0;
    ITS_BOOLEAN isASP = ITS_FALSE;

    if(argc < 4)
    {
        Usage(argv[0]);
    }

    while(i < argc)
    {
        if(strcmp(argv[i], "asp") == 0)  
        {
            isASP = ITS_TRUE;
            appMode = ASP_MODE;
        }
        else if(strcmp(argv[i], "sgp") == 0)
        {
            appMode = SGP_MODE;
        } 
        else if(strcmp(argv[i], "recv") == 0)
        {
            recv_mode = ITS_TRUE;
        }
        else if(strcmp(argv[i], "send") == 0)
        {
            recv_mode = ITS_FALSE;
        } 
        else if(strcmp(argv[i], "opc") == 0)
        {
            LOCAL_PC = atoi(argv[++i]);
        }
        else if(strcmp(argv[i], "dpc") == 0)
        {
            REMOTE_PC = atoi(argv[++i]);
        }

        i++;
    }

    ENGINE_Initialize(argc, argv, NULL, 0);
    ENGINE_Run(argc, argv);

    return 0;
}

void Usage(const char* var)
{
   cout << var << "[asp|sgp] -configFile myApp.xml [recv|send]" << endl;

   return;
}
