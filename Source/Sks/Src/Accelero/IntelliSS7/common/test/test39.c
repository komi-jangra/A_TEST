
#include <its_dsm.h>
#include <its_trace.h>
#include <stdlib.h>
#include <sys/timeb.h>

static ITS_ClassRec classRec;
ITS_Class itsSS7STANDALONE_Class = &classRec;

int
main(int argc, char **argv)
{
    int i;
    time_t now;                   /* Current time */
    struct tm *now_time;
    char temptime[256]; 
    struct _timeb tstruct;

    if (ITS_AddFeature(itsDSM_StubImplClass) != ITS_SUCCESS)
    {
        fprintf(stderr, "AddFeature failed.\n");

        return (EXIT_FAILURE);
    }

    if (ITS_GlobalStart(0) != ITS_SUCCESS)
    {
        fprintf(stderr, "GlobalStart failed.\n");

        return (EXIT_FAILURE);
    }

    /*
     * Set up the timestamp string  
     */
    time(&now);
    now_time = localtime(&now);
    _ftime(&tstruct);
    strftime(temptime, sizeof(temptime), "[%b%d %Y %H:%M:%S]: ", now_time);     
    
    printf("Now: %s.%d\n", temptime, tstruct.millitm);

    ITS_TRACE_CRITICAL(("Application starting...\n"));

    ITS_TRACE_ERROR(("No error\n"));

    ITS_TRACE_WARNING(("No warning.\n"));

    for (i = 0; i < 100000; i++)
    {
        ITS_TRACE_DEBUG(("Loop iteration: %d\n", i));
    }

    time(&now);
    now_time = localtime(&now);
    _ftime(&tstruct);
    strftime(temptime, sizeof(temptime), "[%b%d %Y %H:%M:%S]: ", now_time);     

    printf("Finish: %s.%d\n", temptime, tstruct.millitm);

    ITS_GlobalStop();

    ITS_RemFeature(itsDSM_StubImplClass);

    return (EXIT_SUCCESS);
}
