/*------------------------------------------------------------------------------
 *
 * Test9.
 *
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <conio.h>

#if defined(WIN32)
#include <crtdbg.h>
#endif /* defined(WIN32) */

#include <its.h>
#include <its_ss7_stubs.h>

#include <asn_common.h>

#include <test9_bar1_c.h>
#include <test9_bar10_c.h>
#include <test9_bar2_c.h>
#include <test9_bar3_c.h>
#include <test9_bar4_c.h>
#include <test9_bar5_c.h>
#include <test9_bar6_c.h>
#include <test9_bar7_c.h>
#include <test9_bar8_c.h>
#include <test9_bar9_c.h>
#include <test9_its_feature_class_c.h>


#if defined(WIN32)

/*
 *  The following macros set and clear, respectively, given bits of the C 
 *  runtime library debug flag, as specified by a bitmask.
 */

#if defined(_DEBUG)

#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

#else /* !defined(_DEBUG) */

#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)

#endif /* defined(_DEBUG) */

#endif /* defined(WIN32) */


static int TestLRF();
static int TestSpeedAndMemory();

static ITS_BOOLEAN testPrint = ITS_TRUE;


int 
main(int argc, char** argv)
{
    int res = ITS_SUCCESS;

#if defined(WIN32)

    /*
     *  Note: MUST NOT be enabled if TestSpeedAndMemory. Responsible for using
     *  all the available heap memory (like an invisible leak).
     *
     */
    
    /*
     * Send all reports to STDOUT.
     */

    /*

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    */

    /*
     *  Set the debug-heap flag so that freed blocks are kept on the linked
     *  list, to catch any inadvertent use of freed memory
     *
     */ 

    /* SET_CRT_DEBUG_FIELD(_CRTDBG_DELAY_FREE_MEM_DF); */


    /*
     *  Set the debug-heap flag so that memory leaks are reported when the
     *  process terminates. Then, exit.
     *
     */

    /* SET_CRT_DEBUG_FIELD(_CRTDBG_LEAK_CHECK_DF); */

#endif /* defined(WIN32) */

    printf("Begin test...\n");

    res = ITS_AddFeature(itsASN_C_RUNTIME_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    res = ITS_AddFeature(itsTEST9_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    res = ITS_GlobalStart(0);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    res = TestLRF();

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*

    res = TestSpeedAndMemory();

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    */
    
    ITS_GlobalStop();

    ITS_RemFeature(itsASN_C_RUNTIME_Class);

    ITS_RemFeature(itsTEST9_Class);

    printf("End of test...\n");

    /* To stop here in console application. */

    printf("Type any key to quit...\n");

    {
        char c = getch();
    }

    return EXIT_SUCCESS;
}


int 
TestLRF()
{


    return ITS_SUCCESS;
}


int
TestSpeedAndMemory()
{
    long i = 0;

    printf("\nBegin performance test (code/decode)...\n");

    testPrint = ITS_FALSE;

    for (i = 0; i < 10000l; i++)
    {
       int res = TestLRF();
    }

    testPrint = ITS_TRUE;

    printf("\nEnd performance test (code/decode)...\n");

    return ITS_SUCCESS;
}