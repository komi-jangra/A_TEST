#include <its++.h>
#include <its_route.h>

#include <dbc.h>

using namespace std;
using namespace its;

void
AppDbcServer::DoCommand(istream& commandLine)
{
    if (Cmd("irt", "IntelliSS7 routes", ""))
    {
        char* strDump = (char*) malloc(1024);

        int res = ROUTE_DumpSS7ToIdHashtable(&strDump);

        if (res != ITS_SUCCESS)
        {
            free(strDump);
            oss << "Unable to proceed - dump fatal error." << endl;
        }

        free(strDump);

        oss << strDump;
        oss << endl;
    }
    else if (Cmd("dumpLinkSets", "Dump Link Sets", "<>"))
    {
        char *dump = NULL;

        ROUTE_LockTable();

        LINKSET_DumpLinkSetHashtable(&dump);

        if (dump)
        {
            oss << dump;
            oss << endl;
            free(dump);
        }
    }
}
