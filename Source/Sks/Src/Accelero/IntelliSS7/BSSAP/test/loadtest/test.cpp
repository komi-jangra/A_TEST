#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>

#include <its.h>
#include <its++.h>
#include <engine.h>
#include <its_thread_pool.h>
#include <its_work_item.h>
#include <its_mutex.h>
#include <mtmalloc.h>

extern "C"
{
int
main(int argc, const char **argv)
{
const char *fn;
	ENGINE_Initialize(argc, argv, NULL, 0);
	ENGINE_Run(argc, argv);



}


}


