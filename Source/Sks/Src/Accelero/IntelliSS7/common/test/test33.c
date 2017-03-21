
#include <its_app.h>
#include <its_link.h>
#include <its_timers.h>
#include <its_assertion.h>
#include <its_trace.h>

int
main(int argc, char **argv)
{
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
    RESFILE_Manager *appRes;
    int ret;

    APPL_SetName("oldtest");

    ret = ITS_GlobalStart(0);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    appRes = RESFILE_CreateResourceManager(APPL_GetConfigFileName());
    ITS_C_ASSERT(appRes != NULL);

    ret = LINK_ParseLinkInfo(1, appRes, "Default-Transport1");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ls = LINKSET_FindLinkSet(1);
    ITS_C_ASSERT(ls != NULL);

    ln = LINK_FindLink(1, 0);
    ITS_C_ASSERT(ln != NULL);
    LINKSET_AddActiveLink(ls, ln->linkCode);
    ln = LINK_FindLink(1, 1);
    ITS_C_ASSERT(ln != NULL);
    LINKSET_AddActiveLink(ls, ln->linkCode);
    ln = LINK_FindLink(1, 2);
    ITS_C_ASSERT(ln != NULL);
    LINKSET_AddActiveLink(ls, ln->linkCode);

    ITS_TRACE_DEBUG(("####### START\n"));
    LINKSET_PrintCodeMap(ls);

    LINKSET_RemoveActiveLink(ls, ln->linkCode);
    ITS_TRACE_DEBUG(("####### REM 1\n"));
    LINKSET_PrintCodeMap(ls);

    ln = LINK_FindLink(1, 2);
    LINKSET_RemoveActiveLink(ls, ln->linkCode);
    ITS_TRACE_DEBUG(("####### REM 2\n"));
    LINKSET_PrintCodeMap(ls);

    ln = LINK_FindLink(1, 1);
    LINKSET_AddActiveLink(ls, ln->linkCode);
    ITS_TRACE_DEBUG(("####### ADD 1\n"));
    LINKSET_PrintCodeMap(ls);

    ln = LINK_FindLink(1, 2);
    LINKSET_AddActiveLink(ls, ln->linkCode);
    ITS_TRACE_DEBUG(("####### ADD 2\n"));
    LINKSET_PrintCodeMap(ls);

    TIMERS_Sleep(1);

    ITS_GlobalStop();

    return (0);
}

